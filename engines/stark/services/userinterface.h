/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef STARK_SERVICES_USER_INTERFACE_H
#define STARK_SERVICES_USER_INTERFACE_H

#include "common/rect.h"
#include "common/str-array.h"

namespace Stark {

namespace Gfx {
class Driver;
}

class ActionMenu;
class DialogPanel;
class InventoryWindow;
class TopMenu;
class Cursor;
class FMVPlayer;
class GameWindow;
class Window;

/**
 * Facade object for interacting with the user interface from the rest of the engine
 *
 * @todo: perhaps move all window management to a new class
 * @todo: perhaps introduce a 'Screen' class or just a window with sub-windows for the game screen
 */
class UserInterface {
public:
	UserInterface(Gfx::Driver *gfx);
	virtual ~UserInterface();

	enum Screen {
		kScreenGame,
		kScreenFMV
	};

	void init();
	void update();
	void render();
	void handleMouseMove(const Common::Point &pos);
	void handleClick();
	void handleRightClick();
	void handleDoubleClick();
	void notifyShouldExit() { _exitGame = true; }
	void inventoryOpen(bool open);
	bool shouldExit() { return _exitGame; }

	/** Start playing a FMV */
	void requestFMVPlayback(const Common::String &name);

	/** FMV playback has just ended */
	void onFMVStopped();

	/**
	 * Abort the currently playing FMV, if any
	 *
	 * @return true if a FMV was skipped
	 */
	bool skipFMV();

	/** Set the currently displayed screen */
	void changeScreen(Screen screen);

	/** Is the game screen currently displayed? */
	bool isInGameScreen() const;

	/** Is the inventory panel being displayed? */
	bool isInventoryOpen() const;

	/** Can the player interact with the game world? */
	bool isInteractive() const;

	/** Allow or forbid interaction with the game world */
	void setInteractive(bool interactive);

	int16 getSelectedInventoryItem() const;

	/** Set the selected inventory item */
	void selectInventoryItem(int16 itemIndex);

	/** Clears all the pointers to data that may be location dependent */
	void clearLocationDependentState();

	/** Open the in game options menu */
	void optionsOpen();

private:
	typedef void (Window::*WindowHandler)();
	void dispatchEvent(WindowHandler handler);

	// Game Screen windows
	ActionMenu *_actionMenu;
	DialogPanel *_dialogPanel;
	InventoryWindow *_inventoryWindow;
	TopMenu *_topMenu;
	GameWindow *_gameWindow;

	// Game screen windows array
	Common::Array<Window *> _gameScreenWindows;

	// FMV screen window
	FMVPlayer *_fmvPlayer;

	Gfx::Driver *_gfx;
	Cursor *_cursor;
	bool _exitGame;

	Screen _currentScreen;
	bool _interactive;
};

} // End of namespace Stark

#endif // STARK_SERVICES_USER_INTERFACE_H
