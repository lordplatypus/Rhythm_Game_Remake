# Rhythm_Game_Remake

A rhythm game that is heavily inspired by "Crypt of the NecroDancer." 
Made with SFML.

###### Game Manual / Tutorial
- Japanese - [Here](https://drive.google.com/file/d/1BosJBSg2Yh1-72A3vSW_HMLDN2MNpa71/view?usp=sharing)
- English - In game tutorial available

###### Prerequisites
- cmake(3.18) or higher
- SFML 2.4 or higher

###### Build Instructions
- Clone this repository
```
git clone https://github.com/lordplatypus/Rhythm_Game_Remake.git
```
- Move to the source
```
cd ./Rhythm_Game_Remake
```
- Make a build directory and move to it
```
mkdir ./build && cd ./build
```
- Use cmake to generate the make files into the build folder
```
cmake -S ../ -B ./
```
- Make
```
make
```
- Move the "Resources" folder from the source files to the build folder
```
mv ../Resources ./
```
- Run the Game
```
./Game
```
