#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Tweening.h"

struct SDL_Texture;

class UIelement
{
public:
	UIelement()
	{
		x = 0, y = 0, w = 0, h = 0;
	}
	~UIelement() {}

	void Set(int x, int y, int w, int h)
	{
		x -= w / 2;
		y -= h / 2;

		this->x = x;
		this->y = y; 
		this->w = w;
		this->h = h;

		
	}
	int x, y, w, h;
	

private:

};


class UIbutton : public UIelement
{
public:
	UIbutton() : clicked(false) {}
	~UIbutton(){}
	bool OnMouseOver() 
	{

		int x_, y_;
		app->input->GetMousePosition(x_, y_);
		if (x_ > x && x_ < (x + w) &&
			y_ > y && y_ < (y + h))
		{
			return true;
		}
		else return false;
	}

	bool OnMouseDown()
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT))
		{
			clicked = true;
			return true;
		}
		else return false;
	}

	bool OnMouseRelease()
	{
		if (!app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) && clicked)
		{
			clicked = false;
			return true;
		}
		else return false;
	}
private:

	bool clicked;
};

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* panel;
	SDL_Texture* pause_button;
	SDL_Texture* play_button;

	UIelement UIpanel;
	UIbutton UIpauseButton;
	UIbutton UIplayButton;

	Tween tw_pauseButton_hold;
	Tween tw_panel;
	Tween tw_playButton_appear;

	bool panelOpen;

};




#endif // __SCENE_H__