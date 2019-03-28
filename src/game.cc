//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <game.h>
#include <window.h>
#include <defines.h>
#include <debug_draw.h>

#include <cstdio>

void Game::init() {
	font_ = TTF_OpenFont(FONT_FILE, FPS_FONT_SIZE);
	if (!font_) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	fps_sprite_.setVisible(false);

	world_.target()->getKinematic()->position = MathLib::Vec2(0.0f, 0.0f);
}

void Game::start() {
	uint32_t fps_time{ 0 };
	uint32_t fps_time_acc{ 0 };

	uint32_t next_game_tick = SDL_GetTicks();
	uint32_t update_loops = 0;
	uint32_t render_loops = 0;

	const uint32_t skip_ticks = 1000 / TICKS_PER_SECOND;

	while (!quit_) {
		uint32_t loops = 0;
		while ((SDL_GetTicks() > next_game_tick) && (loops < MAX_FRAME_SKIP)) {
			handleInput();
			update(skip_ticks);

			next_game_tick += skip_ticks;
			++loops;
			++update_loops;
		}

		render();

		uint32_t c_time = SDL_GetTicks();
		fps_time_acc += (c_time - fps_time);
		fps_time = c_time;
		++render_loops;
		if (render_loops > 100) {        //show stats each 100 frames
			const float fps = 1000.0f / (fps_time_acc / 100.0f);
			const float ratio = (float)render_loops / (float)update_loops;
			char text[255];
			sprintf_s(text, "%d RFPS      %d UFPS", (uint32_t)fps, (uint32_t)(fps / ratio));
			fps_sprite_.loadFromRenderedText(text, SDL_Color FOREGROUND_COLOR, font_, true);
			fps_sprite_.setVisible(true);

			render_loops = 0;
			update_loops = 0;
			fps_time_acc = 0;
		}
	}
}

void Game::shutdown() {}

void Game::handleInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit_ = true;
		}

		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			if (e.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState(&x, &y);

				world_.target()->getKinematic()->position = Vec2(x, y);
			}
		}

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE: quit_ = true; break;
			case SDLK_F3:
				slo_mo_ = clamp<int8_t>(++slo_mo_, 1, 10);
				printf("Slow Motion Set To %d\n", slo_mo_);
				break;
			case SDLK_F4:
				slo_mo_ = clamp<int8_t>(--slo_mo_, 1, 10);
				printf("Slow Motion Set To %d\n", slo_mo_);
				break;
			case SDLK_F5:
				DebugDraw::toggleEnabled();
				printf("Debug Draw Mode Changed\n");
				break;
			case SDLK_UP: {
				world_.target()->getKinematic()->speed += 20.0f;
				if (world_.target()->getKinematic()->speed > 140.0f) {
					world_.target()->getKinematic()->speed = 140.0f;
				}
				break; }
			case SDLK_DOWN: {
				world_.target()->getKinematic()->speed -= 20.0f;
				if (world_.target()->getKinematic()->speed <= 0.0f) {
					world_.target()->getKinematic()->speed = 0.0f;
				}
				break; }
			case SDLK_LEFT: {
				world_.target()->getKinematic()->orientation -= 0.2f;
				break;
			}
			case SDLK_RIGHT: {
				world_.target()->getKinematic()->orientation += 0.2f;
				break;
			}
			case SDLK_1:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Kinematic_Seek);
				}          printf("Behavior Of Agent Changed To Kinematic_Seek\n");
				break;
			case SDLK_2:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Kinematic_Flee);
				}          printf("Behavior Of Agent Changed To Kinematic_Flee\n");
				break;
			case SDLK_3:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Kinematic_Arrive);
				}				printf("Behavior Of Agent Changed To Kinematic_Arrive\n");
				break;
			case SDLK_4:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Kinematic_Wander);
				}				printf("Behavior Of Agent Changed To Kinematic_Wander\n");
				break;
			case SDLK_q:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Seek);
				}				printf("Behavior Of Agent Changed To Seek\n");
				break;
			case SDLK_w:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Flee);
				}				printf("Behavior Of Agent Changed To Flee\n");
				break;
			case SDLK_e:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Arrive);
				}				printf("Behavior Of Agent Changed To Arrive\n");
				break;
			case SDLK_r:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Align);
				}				printf("Behavior Of Agent Changed To Align\n");
				break;
			case SDLK_t:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Velocity_Matching);
				}				printf("Behavior Of Agent Changed To Velocity_Matching\n");
				break;
			case SDLK_a:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Pursue);
				}				printf("Behavior Of Agent Changed To Pursue\n");
				break;
			case SDLK_s:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Face);
				}				printf("Behavior Of Agent Changed To Face\n");
				break;
			case SDLK_d:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::LookGoing);
				}				printf("Behavior Of Agent Changed To LookGoing\n");
				break;
			case SDLK_f:
				for (int i = 0; i < MAX_AGENTS; i++) {
					world_.ia(i)->setSteering(Body::SteeringMode::Wander);
				}				printf("Behavior Of Agent Changed To Wander\n");
				break;

			case SDLK_g:
				for (int i = 0; i < MAX_AGENTS; i++) {
					Steering steer;
					/*world_.ia(i + 1)*/
					Cohesion cohesion;
					cohesion.calculate(world_.ia(i)->getKinematic(), world_.ia(i + 1)->getKinematic(), &steer);
					world_.ia(i)->body_.updateSteering(dt, steer);
					setOrientation(state_.velocity);
				}
				printf("Behavior Of Agent Changed To Cohesion\n");
				break;
			}
		}
	}
}

void Game::update(const uint32_t dt) {
	world_.update(dt / slo_mo_);
}

void Game::render() {
	SDL_Renderer* renderer = Window::instance().getRenderer();
	SDL_SetRenderDrawColor(renderer, 0xD0, 0xD0, 0xD0, 0xFF);
	SDL_RenderClear(renderer);

	fps_sprite_.render();
	world_.render();
	DebugDraw::render();

	SDL_RenderPresent(renderer);
}