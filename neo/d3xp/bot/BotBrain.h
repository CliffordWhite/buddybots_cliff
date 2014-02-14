/*
===========================================================================
File: BotBrain.h
Author: John Wileczek
Description: Defines the basic interface that bot brains should follow.
===========================================================================
*/
#ifndef BOTBRAIN_H_
#define BOTBRAIN_H_

class afiBotPlayer;
class idAAS;
class idPhysics_Player;

enum aiViewType_t {
	VIEW_DIR,
	VIEW_POS
};

enum aiMoveFlag_t {
	NULLMOVE = 0,
	CROUCH,
	JUMP,
	WALK,
	RUN
};

struct aiCommands_t {
	bool attack;
	bool zoom;
};

struct aiInput_t {
	idVec3				viewDirection;
	aiViewType_t		viewType;
	idVec3				moveDirection;
	float				moveSpeed;
	aiMoveFlag_t		moveFlag;
	aiCommands_t		commands;
};

/*
===============================================================================

afiBotBrain
This will serve as the base class that all bot brains should be derived off of.
This will define the basic interface that bots must adhere to, to maintain
proper communication with the body of the bot.
*NOTE* Still unsure if this class should be derived off of idEntity or keep
it completely seperate from their hierarchy. This would have to be derived
from idEntity if we want to make use of DoomScript and TypeInfo of the brain
===============================================================================
*/

class afiBotBrain
{
public:
	//							afiBotBrain();
	//virtual						~afiBotBrain();

	//Pure Virtual Bot Interface
	virtual aiInput_t			Think() = 0;
	virtual void				Spawn() = 0;
	virtual void				Restart() = 0;
	//TODO: Event Handling functions.
	//virtual void OnPain(idEntity* inflictor, idEntity* attacker, int damage);
	//virtual void OnDisconnect();
	//virtual void OnKill();
	//virtual void OnDeath();

	//Accessors and Mutators
	void						SetAAS( void );
	void						SetBody(afiBotPlayer* newBody);
	void						SetPhysics(idPhysics_Player* _physicsObject);
public:

	afiBotPlayer*		GetBody();
	idPhysics_Player*			GetPhysics();
	//Pointer to the fake client body of the bot.
	afiBotPlayer*		body;
	object						scriptBody;
	idPhysics_Player*			physicsObject;
	// navigation
	idAAS *						aas;
	int							travelFlags;

	//This will be the same spawn dict as the body
	//so the student can fill the one entityDef and
	//have access to those pairs in the brain.
	dict						botDict;

	aiInput_t					bodyInput;

private:
};

class afiBotBrainWrapper : public afiBotBrain,public wrapper<afiBotBrain> {
public:

	virtual aiInput_t Think();

	virtual void Spawn();

	virtual void Restart();
};

#endif