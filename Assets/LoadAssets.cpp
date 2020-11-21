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

    LP::SetTexture(hearts_texture, "./Resources/Images/Player/Hearts.png", 64, 16);
    LP::SetTexture(bps_scene_texture, "./Resources/Images/BPMScene.png", 1080, 720);
    LP::SetTexture(roboko_texture, "./Resources/Images/Player/Player_Roboko.png", 256, 320);

    //Player hearts(プレーヤーのハート)
    LP::SetTexture(heart_texture, "./Resources/Images/Player/Heart.png", 16, 16);
    LP::SetTexture(heart_small_texture, "./Resources/Images/Player/HeartSmall.png", 16, 16);
    LP::SetTexture(grey_heart_texture, "./Resources/Images/Player/GreyHeart.png", 16, 16);
    LP::SetTexture(grey_heart_small_texture, "./Resources/Images/Player/GreyHeartSmall.png", 16, 16);

    //Particle
    LP::SetTexture(white_texture, "./Resources/Images/Particle/Particle_White.png", 1080, 720);
    LP::SetTexture(fire_texture, "./Resources/Images/Particle/particle_fire.png", 128, 128);
    LP::SetTexture(square_texture, "./Resources/Images/Particle/particle_square8x8.png", 8, 8);
    LP::SetTexture(smoke_texture, "./Resources/Images/Particle/particle_smoke.png", 128, 128);
    LP::SetTexture(sparkle_texture, "./Resources/Images/Particle/particle_sparkle_1.png", 128, 128);
    LP::SetTexture(slash_texture, "./Resources/Images/Particle/Particle_Line32x32.png", 32, 32);
    LP::SetTexture(up_arrow_L_texture, "./Resources/Images/Particle/Particle_UpArrowL.png", 8, 8);
    LP::SetTexture(up_arrow_R_texture, "./Resources/Images/Particle/Particle_UpArrowR.png", 8, 8);
    LP::SetTexture(down_arrow_L_texture, "./Resources/Images/Particle/Particle_DownArrowL.png", 8, 8);
    LP::SetTexture(down_arrow_R_texture, "./Resources/Images/Particle/Particle_DownArrowR.png", 8, 8);
    LP::SetTexture(left_arrow_L_texture, "./Resources/Images/Particle/Particle_LeftArrowL.png", 8, 8);
    LP::SetTexture(left_arrow_R_texture, "./Resources/Images/Particle/Particle_LeftArrowR.png", 8, 8);
    LP::SetTexture(right_arrow_L_texture, "./Resources/Images/Particle/Particle_RightArrowL.png", 8, 8);
    LP::SetTexture(right_arrow_R_texture, "./Resources/Images/Particle/Particle_RightArrowR.png", 8, 8);

    //Arrow
    LP::SetTexture(up_arrow_texture, "./Resources/Images/Arrow/UpArrow.png", 8, 8);
    LP::SetTexture(up_arrow_grey_texture, "./Resources/Images/Arrow/UpArrowGrey.png", 8, 8);
    LP::SetTexture(down_arrow_texture, "./Resources/Images/Arrow/DownArrow.png", 8, 8);
    LP::SetTexture(down_arrow_grey_texture, "./Resources/Images/Arrow/DownArrowGrey.png", 8, 8);
    LP::SetTexture(left_arrow_texture, "./Resources/Images/Arrow/LeftArrow.png", 8, 8);
    LP::SetTexture(left_arrow_grey_texture, "./Resources/Images/Arrow/LeftArrowGrey.png", 8, 8);
    LP::SetTexture(right_arrow_texture, "./Resources/Images/Arrow/RightArrow.png", 8, 8);
    LP::SetTexture(right_arrow_grey_texture, "./Resources/Images/Arrow/RightArrowGrey.png", 8, 8);

    //Enemies(敵)
    LP::SetTexture(companion_texture, "./Resources/Images/Enemy/Enemy_Robot_Companion.png", 256, 32);
    LP::SetTexture(surveillance_texture, "./Resources/Images/Enemy/Enemy_Robot_Surveillance.png", 128, 64);
    LP::SetTexture(ghost_texture, "./Resources/Images/Enemy/Enemy_Robot_Ghost.png", 128, 64);
    LP::SetTexture(crawler_texture, "./Resources/Images/Enemy/Enemy_Robot_Crawler.png", 192, 64);

    //Item(アイテム)
    LP::SetTexture(part_screw_texture, "./Resources/Images/Item/Part_Screw.png", 7, 7);
    LP::SetTexture(part_nut_texture, "./Resources/Images/Item/Part_Nut.png", 8, 8);
    LP::SetTexture(part_battery_texture, "./Resources/Images/Item/Part_Battery.png", 8, 8);
    LP::SetTexture(part_spring_texture, "./Resources/Images/Item/Part_Spring.png", 15, 5);
    LP::SetTexture(part_dark_spring_texture, "./Resources/Images/Item/Part_Dark_Spring.png", 15, 5);
    LP::SetTexture(item_heal_texture, "./Resources/Images/Item/Item_Heal.png", 32, 32);
    LP::SetTexture(item_maxHP_texture, "./Resources/Images/Item/Item_MaxHP.png", 32, 32);
    LP::SetTexture(item_range_texture, "./Resources/Images/Item/Item_Range.png", 32, 32);
    LP::SetTexture(item_special_cooldown_texture, "./Resources/Images/Item/Item_Special.png", 32, 32);
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