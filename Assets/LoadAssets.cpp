#include <iostream>
#include "LoadAssets.h"
#include "ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"

LoadAssets::LoadAssets()
{}

LoadAssets::~LoadAssets()
{}

void LoadAssets::Load()
{
    LoadImage();
    LoadSound();
}

void LoadAssets::LoadImage()
{
    // LP::SetFont("Path to Font");
    // LP::SetTexture(Texture Key, "Path to texture", texture width, texture height);
    LP::SetFont("./Resources/Font/Blue Sky 8x8.ttf");

    //TileMap Texture(タイルマップテクスチャ)
    LP::SetTexture(tile_map, "./Resources/Images/TileMap/Factory_TileMap.png", 256, 256);
    LP::SetTexture(tile_map_details, "./Resources/Images/TileMap/Factory_TileMap_Details.png", 128, 160);

    //Title Scene(タイトルの画像)
    LP::SetTexture(title_scene_texture, "./Resources/Images/Title_Sceen_Background.png", 180, 120);

    LP::SetTexture(heart_texture, "./Resources/Images/Player/Hearts.png", 64, 16);
    LP::SetTexture(bps_scene_texture, "./Resources/Images/BPMScene.png", 1080, 720);
    LP::SetTexture(roboko_texture, "./Resources/Images/Player/Player_Roboko.png", 256, 320);
}

void LoadAssets::LoadSound()
{
    // MP::SetMusic(Music Key, "Path to music");
    // MP::SetSound(Sound Key, "Path to sound clip");
    MP::SetMusic(Remember_Passion_Beat, "./Resources/Audio/Remember Passion Beat.ogg");
    MP::SetMusic(Necro_funk_the_around, "./Resources/Audio/Necro funk the around.ogg");
    MP::SetMusic(Adjust, "./Resources/Audio/Adjust.ogg");
    MP::SetMusic(Southern_Arena, "./Resources/Audio/Southern Arena.ogg");
    MP::SetMusic(Nothing_Can_Stop_Us_Now, "./Resources/Audio/Nothing Can Stop Us Now.ogg");
    MP::SetMusic(Fight_For_Your_Life, "./Resources/Audio/Fight For Your Life.ogg");
    MP::SetMusic(Amaryllis, "./Resources/Audio/Amaryllis.flac");
    MP::SetMusic(Ayahuasca, "./Resources/Audio/Ayahuasca.flac");
    MP::SetMusic(Ceramic_Summer, "./Resources/Audio/Ceramic Summer.ogg");
    MP::SetMusic(La_Tropica, "./Resources/Audio/La Tropica.ogg");
    MP::SetMusic(moonshade_, "./Resources/Audio/moonshade_.flac");
    MP::SetMusic(Reconfig, "./Resources/Audio/Reconfig.ogg");
    MP::SetMusic(Gain_Therapy, "./Resources/Audio/Gain Therapy Edit.ogg");
    MP::SetMusic(Nec_Minus_Ultra, "./Resources/Audio/Nec Minus Ultra.ogg");
    MP::SetMusic(Il_vento_doro_eurobeat, "./Resources/Audio/Il vento d'oro eurobeat remix.wav");
    MP::SetMusic(LAZZULI_LUVS, "./Resources/Audio/02 LAZZULI LUVS_no vocal.ogg");
    MP::SetMusic(DESCENDING_AIR_CURRENT, "./Resources/Audio/03 DESCENDING AIR CURRENT.ogg");
    MP::SetMusic(DETROIT_BEAT, "./Resources/Audio/05 DETROIT BEAT.ogg");
    MP::SetMusic(New_Gear, "./Resources/Audio/12 New Gear.ogg");
    MP::SetMusic(across_battle_result, "./Resources/Audio/24 across battle result.ogg");
}