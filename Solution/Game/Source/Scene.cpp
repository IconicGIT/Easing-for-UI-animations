#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include "ModuleFonts.h"
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	panel = app->tex->Load("Assets/Textures/panel.png");
	pause_button = app->tex->Load("Assets/Textures/pause_button.png");
	play_button = app->tex->Load("Assets/Textures/play_button.png");

	UIpanel.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 696, 332);
	UIpauseButton.Set(WINDOW_WIDTH - 50,50, 80, 80);
	UIplayButton.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 80, 80);

	//	Set the tween for the play button
	tw_pauseButton_hold.Set(0, 100, 25, BOUNCE_OUT);
	tw_pauseButton_hold.Backward();

	//	Set the tween for the panel
	tw_panel.Set(0, 100, 50, BACK_OUT);
	tw_panel.Backward();

	// Set the tween for holding the pause button
	tw_playButton_appear.Set(0, 100, 25, QUARTIC_OUT);
	tw_playButton_appear.Backward();

	panelOpen = false;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	// Update all the tweens
	tw_pauseButton_hold.Step(1, false);
	tw_panel.Step(1, false);
	tw_playButton_appear.Step(1, false);


	//	Get the value of the tweenings for using them in the animations
	float value_pauseButton_anim = tw_pauseButton_hold.GetPoint();
	float value_panel_anim = tw_panel.GetPoint();
	float value_playButton_anim = tw_panel.GetPoint();


	//	Useful variable
	int panel_vertcal_offset = -550;
	
	LOG(".");
	if (UIpauseButton.OnMouseOver() && UIpauseButton.OnMouseDown())
	{
		LOG("mouse down");

		tw_pauseButton_hold.Foward();

	}
	else if (UIpauseButton.OnMouseRelease())
	{
		LOG("released");

		panelOpen = !panelOpen;
		tw_pauseButton_hold.Backward();

	}

	//	Make the animations go foward of backward depending on if the panel is open or not

	if (panelOpen)
	{
		tw_panel.Foward();
		tw_playButton_appear.Foward();
	}
	else
	{
		tw_panel.Backward();
		tw_playButton_appear.Backward();
	}


	app->render->DrawTextureExt(panel, UIpanel.x + UIpanel.w / 2, panel_vertcal_offset + ((UIpanel.y + UIpanel.h / 2) - value_panel_anim * panel_vertcal_offset), 1, 1, 255, NULL, 1, 0, UIpanel.w / 2, UIpanel.h / 2);
	app->render->DrawTextureExt(pause_button, UIpauseButton.x + UIpauseButton.w / 2, UIpauseButton.y + UIpauseButton.h / 2, 1 + value_pauseButton_anim * 0.25f, 1 + value_pauseButton_anim * 0.25f, 255, NULL, 1, 0, UIpauseButton.w / 2, UIpauseButton.h / 2);
	app->render->DrawTextureExt(play_button, UIplayButton.x + UIplayButton.w / 2, UIplayButton.y + UIplayButton.h / 2, value_playButton_anim * 1, value_playButton_anim * 1, 255, NULL, 1, 0, UIplayButton.w / 2, UIplayButton.h / 2);


	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
