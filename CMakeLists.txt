cmake_minimum_required(VERSION 3.18)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_BUILD_TYPE "Debug")

# set the project name
project(Game)

# set path to findSFML.cmake file
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# find SFML components
find_package(SFML 2.4 COMPONENTS graphics window system audio REQUIRED)

# list .cpp files
# set(SOURCES main.cpp LP.cpp Game.cpp SceneGame.cpp LoadAssets.cpp GameObject.cpp GameObjectManager.cpp MP.cpp Camera.cpp IP.cpp Particle.cpp ParticleManager.cpp
# SceneSetBPM.cpp UIVerticalMenu.cpp)

set(SOURCES)

add_subdirectory(Assets)
add_subdirectory(BPMScene)
add_subdirectory(Enemy)
add_subdirectory(Engine)
add_subdirectory(Event)
add_subdirectory(Gameobjects)
add_subdirectory(Item)
add_subdirectory(JunkYardScene)
add_subdirectory(LobbyScene)
add_subdirectory(Map)
add_subdirectory(MusicSelect)
add_subdirectory(Particle)
add_subdirectory(Player)
add_subdirectory(Stage1)
add_subdirectory(StartingItemScene)
add_subdirectory(TestScene)
add_subdirectory(TitleScene)
add_subdirectory(Transition)
add_subdirectory(TutorialScene)
add_subdirectory(UI)


# add the executable
add_executable(Game ${SOURCES})

target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Assets")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/BPMScene")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Enemy")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Engine")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Event")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Gameobjects")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Item")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/JunkYardScene")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/LobbyScene")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Map")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/MusicSelect")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Particle")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Player")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Stage1")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/TestScene")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/TitleScene")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/Transition")
target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/UI")



# link SFML libraries
target_link_libraries(Game sfml-graphics sfml-window sfml-system sfml-audio)