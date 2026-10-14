# Snake Xenzia (Nokia style)

A single-file recreation of the classic Nokia Snake Xenzia, drawn on a 96x65 pixel olive LCD screen. No build step, no dependencies.

## Run it

Open `index.html` in any modern browser. Works on desktop and mobile. (The menu font loads from Google Fonts; it falls back to a monospace font offline.)

To host it, upload `index.html` to any static host (GitHub Pages, Netlify, etc.).

## Controls

| Action | Keyboard | Touch |
| --- | --- | --- |
| Steer / move in menu | Arrow keys, WASD, or 2 / 4 / 6 / 8 | Swipe on the screen |
| Select / pause | Enter, Space, or 5 | Tap a menu row or "Select"; tap the screen to pause |
| Back / pause | Backspace, Esc, or P | Tap "Back" |

## Menu

- **Continue**: appears while a game is paused.
- **New game**: starts a game.
- **Level**: 1 to 9. Higher is faster, and each food scores your level number.
- **Game type**:
  - **Classic**: the snake wraps through the screen edges.
  - **Box**: a wall frame is drawn, and touching it ends the game.

## Gameplay

- Eat the "+" food to grow and score.
- After every 5 foods a big bonus ball appears. Reach it before the bar at the bottom right runs out; the faster you are, the more points you get.
- The game ends if the snake hits its own body (or the wall in Box mode).
- Your best score, level and game type are saved in your browser.

## Files

- `index.html`: the whole game (HTML, CSS and JavaScript in one file).
- `README.md`: this file.
