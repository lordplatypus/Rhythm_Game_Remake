#ifndef ID_H_
#define ID_H_

//Commonly used "keys" that need to have the same value across the whole program
//Ex: texture keys, music keys
enum
{
    bps_scene_texture,
    roboko_texture,
    hearts_texture,

    //TileMap Texture(タイルマップテクスチャ)
    tile_map,
    tile_map_details,

    //Title Sceen(タイトルの画像)
    title_scene_texture,

    //Select Music
    music_select_scene_texture,

    //UI
    heart_texture,
    heart_small_texture,
    grey_heart_texture,
    grey_heart_small_texture,

    //Particle
    white_texture,
    slash_texture,
    square_texture,
    sparkle_texture,
    smoke_texture,
    fire_texture,
    up_arrow_L_texture,
    up_arrow_R_texture,
    down_arrow_L_texture,
    down_arrow_R_texture,
    left_arrow_L_texture,
    left_arrow_R_texture,
    right_arrow_L_texture,
    right_arrow_R_texture,

    //Arrow
    up_arrow_texture,
    up_arrow_grey_texture,
    down_arrow_texture,
    down_arrow_grey_texture,
    left_arrow_texture,
    left_arrow_grey_texture,
    right_arrow_texture,
    right_arrow_grey_texture, 

    //Enemies(敵)
    companion_texture,
    surveillance_texture,
    ghost_texture,
    crawler_texture,
    target_texture,
    artillery_texture,
    bullet_casing_texture,
    generator_texture,
    tower_texture,
    minecart_texture,
    rail_texture,

    //Item
    part_screw_texture,
    part_nut_texture,
    part_battery_texture,
    part_spring_texture,
    part_dark_spring_texture,
    item_heal_texture,
    item_maxHP_texture,
    item_range_texture,
    item_special_cooldown_texture,
    item_sunglassese_texture,
    item_reserve_tank_texture,
    item_emp_texture,
    item_taser_texture,
    item_horseshoe_texture,
    item_key_texture,
    item_spare_parts_texture,
};

enum
{
    // Remember_Passion_Beat,
    // Necro_funk_the_around,
    // Adjust,
    // Southern_Arena,
    // Nothing_Can_Stop_Us_Now,
    // Fight_For_Your_Life,
    // Amaryllis,
    // Ayahuasca,
    // Ceramic_Summer,
    // La_Tropica,
    // moonshade_,
    // Reconfig,
    //Gain_Therapy,
    // Nec_Minus_Ultra,
    // Il_vento_doro_eurobeat,
    LAZZULI_LUVS,
    DESCENDING_AIR_CURRENT,
    DETROIT_BEAT,
    New_Gear,
    across_battle_result,
};

enum
{
    title_scene,
    lobby_scene,
    tutorial,
    //test_scene,
    stage1_1,
    stage1_2,
    stage1_3
};

#endif