#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Box2D/Box2D.h>

#include <stdio.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

int main(){


    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0) {
        fprintf(stderr, "Could not initialize SDL2: %s \n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(
                "JamEngine",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
                );


    //se ha creado correctamente la ventana?
    if (window == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // el render se ha creado?
    if (renderer == NULL) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }

    

  SDL_Texture* imageTexture = NULL;
  SDL_Surface* imageSurface = IMG_Load("assets/logo.png");

    if( imageSurface == NULL ){
            fprintf(stderr, "Error loading image, %s\n", SDL_GetError());
			return -1;

    }else{

        imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        //liberamos la memoria de la surface, desde ahora se usa la texture (gpu)
        SDL_FreeSurface(imageSurface);
    }


    SDL_Rect dst;
    dst.h = 50;
    dst.w = 50;
	dst.x = 200;
	dst.y = 100;



    //Copy paste sample BOX2D

// Define the gravity vector.
	b2Vec2 gravity(10.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(500.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(dst.x, dst.y);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 1000; ++i)
	{
		SDL_RenderClear(renderer);
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

		dst.x = position.x;
		dst.y = position.y;

		SDL_RenderCopy(renderer, imageTexture, NULL, &dst);

		SDL_RenderPresent(renderer);

	  SDL_Delay(5);


	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.



  SDL_DestroyTexture(imageTexture);
  SDL_DestroyWindow(window);

  SDL_Quit();


}