# Welcome to my button (maybe engine idk)
i am trying to replicate the upgrade trees system from some roblox games

its canvas based js

here are my insparation: (both roblox games)

- [The difficulty upgrade tree: regrown](https://www.roblox.com/games/15913854716/The-Difficulty-Upgrade-Tree-Regrown)
- [Everything upgrade tree](https://www.roblox.com/games/122809141833750/Everything-Upgrade-Tree)

## status
### current features:
- a panable, zoomable world map (0, 0) is in center, and thus, most thing has their x, y centered (buttons for now) see [render.js](./scripts/render.js)

- **note** move with wasd click buttons with mouse, touch controls will be added... later

- very customizable (you fucking write your own draw() the type of customizable) elements inside world (there are defaults)

- very custom button behavior ( you HAVE TO write your own requirements and action ) go to [button.js](./scripts/classes/button.js) for more infomation

- (not really) intuitive trees (not really this is a joke)

- jss (javascript style sheets) examples on that in [setup](./scripts/setup/pointTree.js)

- the example is also in the link above.
### missing features ( my todo list)
- links
- ui
- currency (UNACCEPTABLE HOW CAN A INCREMENTAL GAME HAS NO CURRENCY!!!!) // sorry i need to make ui first before currency, as u can see i alr made the currency class in [currency.js](./scripts/classes/currency.js)
- quadtree
- a fuckton more stuff will *probably* come

## notes 
**expect chaos im 14 while writing this and this is my first project**

- it's made with some help from ai, sorry..

- go to [info.md](./docs/general-info.md)