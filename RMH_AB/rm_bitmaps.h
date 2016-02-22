//AI side image 16x24
const unsigned char PROGMEM AIImg_bitmap[] =
{
  //     ######      
  //   ## ##   ####  
  //  #  #  #   #  # 
  // #  #  # #   #  #
  //  # #    #  # # #
  //   # #  #   # # #
  //    # ##    #  ##
  // ####       #  ##
  // #   #     #    #
  //  #        ###  #
  //   #      #   # #
  //    # #####   # #
  //    #      #### #
  //     #       #  #
  //      ##    #  # 
  //     #     # ##  
  //    #     #  #   
  //   #    ##    #  
  //   #   #  #   #  
  //    #   #  #   # 
  //     #  #   #   #
  //      #  #   #  #
  //       # #    # #
  //        #      # 
  0x88, 0x94, 0xA2, 0xDA, 0x25, 0x43, 0x4B, 0x25, 0x19, 0x01, 0x02, 0xF6, 0x0A, 0x32, 0xC4, 0xF8, 
  0x01, 0x02, 0x04, 0x18, 0xA1, 0x48, 0x48, 0x08, 0x08, 0x0C, 0x93, 0x52, 0xB2, 0x9C, 0x40, 0x3F, 
  0x00, 0x00, 0x06, 0x09, 0x10, 0x20, 0x44, 0x9A, 0x62, 0x05, 0x08, 0x10, 0x21, 0x46, 0x88, 0x70, 
};

const unsigned char PROGMEM AIkick_bitmap[] =
{
  //     ######      
  //   ## ##   ####  
  //  #  #  #   #  # 
  // #  #  # #   #  #
  //  # #    #  # # #
  //   # #  #   # # #
  //    # ##    #  ##
  // ####       #  ##
  // #   #     #    #
  //  #        ###  #
  //   #      #   # #
  //    # #####   # #
  //    #      #### #
  //     #       #  #
  //      ##    #  # 
  //      #    # ##  
  //     #    #  #   
  //    #    #    #  
  //   #    # #   #  
  //  #    #   #   # 
  // #    #     #   #
  // #  ##       #  #
  // # #          # #
  // ##            # 
  0x88, 0x94, 0xA2, 0xDA, 0x25, 0x43, 0x4B, 0x25, 0x19, 0x01, 0x02, 0xF6, 0x0A, 0x32, 0xC4, 0xF8, 
  0x01, 0x02, 0x04, 0x18, 0x21, 0xC8, 0x48, 0x08, 0x08, 0x0C, 0x93, 0x52, 0xB2, 0x9C, 0x40, 0x3F, 
  0xF0, 0x88, 0x44, 0x22, 0x21, 0x10, 0x08, 0x04, 0x02, 0x05, 0x08, 0x10, 0x21, 0x46, 0x88, 0x70, 
};

const unsigned char PROGMEM AIhitFace_bitmap[] =
{
  //     ######      
  //    # ##   ####  
  //   # #  #   #  # 
  //  # # ## #   #  #
  //  # #  # #  # # #
  //   # #  #   # # #
  //    # ##    #  ##
  //  ###       #  ##
  //  #  #     #    #
  //  #        ###  #
  //   #      #   # #
  //    # #####   # #
  //    #      #### #
  //     #       #  #
  //      ##    #  # 
  //     #     # ##  
  //    #     #  #   
  //   #    ##    #  
  //   #   #  #   #  
  //    #   #  #   # 
  //     #  #   #   #
  //      #  #   #  #
  //       # #    # #
  //        #      # 
  0x00, 0x98, 0xA4, 0xDA, 0x25, 0x4B, 0x5B, 0x25, 0x19, 0x01, 0x02, 0xF6, 0x0A, 0x32, 0xC4, 0xF8, 
  0x00, 0x03, 0x04, 0x18, 0xA1, 0x48, 0x48, 0x08, 0x08, 0x0C, 0x93, 0x52, 0xB2, 0x9C, 0x40, 0x3F, 
  0x00, 0x00, 0x06, 0x09, 0x10, 0x20, 0x44, 0x9A, 0x62, 0x05, 0x08, 0x10, 0x21, 0x46, 0x88, 0x70, 
};

const unsigned char *AI_bitmaps[] = {
  AIImg_bitmap, AIkick_bitmap, AIhitFace_bitmap
};


//Player side image 16x24
const unsigned char PROGMEM playerImg_bitmap[] =
{
  //       ######    
  //   ####   ## ##  
  //  #  #   #  #  # 
  // #  #   # #  #  #
  // # # #  #    # # 
  // # # #   #  # #  
  // ##  #    ## #   
  // ##  #       ####
  // #    #     #   #
  // #  ###        # 
  // # #   #      #  
  // # #   ##### #   
  // # ####      #   
  // #  #       #    
  //  #  #    ##     
  //   ## #     #    
  //    #  #     #   
  //   #    ##    #  
  //   #   #  #   #  
  //  #   #  #   #   
  // #   #   #  #    
  // #  #   #  #     
  // # #    # #      
  //  #      #       
  0xF8, 0xC4, 0x32, 0x0A, 0xF6, 0x02, 0x01, 0x19, 0x25, 0x4B, 0x43, 0x25, 0xDA, 0xA2, 0x94, 0x88, 
  0x3F, 0x40, 0x9C, 0xB2, 0x52, 0x93, 0x0C, 0x08, 0x08, 0x48, 0x48, 0xA1, 0x18, 0x04, 0x02, 0x01, 
  0x70, 0x88, 0x46, 0x21, 0x10, 0x08, 0x05, 0x62, 0x9A, 0x44, 0x20, 0x10, 0x09, 0x06, 0x00, 0x00, 
};

const unsigned char PROGMEM playerKick_bitmap[] =
{
  //       ######    
  //   ####   ## ##  
  //  #  #   #  #  # 
  // #  #   # #  #  #
  // # # #  #    # # 
  // # # #   #  # #  
  // ##  #    ## #   
  // ##  #       ####
  // #    #     #   #
  // #  ###        # 
  // # #   #      #  
  // # #   ##### #   
  // # ####      #   
  // #  #       #    
  //  #  #    ##     
  //   ## #    #     
  //    #  #    #    
  //   #    #    #   
  //   #   # #    #  
  //  #   #   #    # 
  // #   #     #    #
  // #  #       ##  #
  // # #          # #
  //  #            ##
  0xF8, 0xC4, 0x32, 0x0A, 0xF6, 0x02, 0x01, 0x19, 0x25, 0x4B, 0x43, 0x25, 0xDA, 0xA2, 0x94, 0x88, 
  0x3F, 0x40, 0x9C, 0xB2, 0x52, 0x93, 0x0C, 0x08, 0x08, 0x48, 0xC8, 0x21, 0x18, 0x04, 0x02, 0x01, 
  0x70, 0x88, 0x46, 0x21, 0x10, 0x08, 0x05, 0x02, 0x04, 0x08, 0x10, 0x21, 0x22, 0x44, 0x88, 0xF0, 
};

const unsigned char PROGMEM playerhitFace_bitmap[] =
{
  //       ######    
  //   ####   ## #   
  //  #  #   #  # #  
  // #  #   # ## # # 
  // # # #  # #  # # 
  // # # #   #  # #  
  // ##  #    ## #   
  // ##  #       ### 
  // #    #     #  # 
  // #  ###        # 
  // # #   #      #  
  // # #   ##### #   
  // # ####      #   
  // #  #       #    
  //  #  #    ##     
  //   ## #     #    
  //    #  #     #   
  //   #    ##    #  
  //   #   #  #   #  
  //  #   #  #   #   
  // #   #   #  #    
  // #  #   #  #     
  // # #    # #      
  //  #      #       
  0xF8, 0xC4, 0x32, 0x0A, 0xF6, 0x02, 0x01, 0x19, 0x25, 0x5B, 0x4B, 0x25, 0xDA, 0xA4, 0x98, 0x00, 
  0x3F, 0x40, 0x9C, 0xB2, 0x52, 0x93, 0x0C, 0x08, 0x08, 0x48, 0x48, 0xA1, 0x18, 0x04, 0x03, 0x00, 
  0x70, 0x88, 0x46, 0x21, 0x10, 0x08, 0x05, 0x62, 0x9A, 0x44, 0x20, 0x10, 0x09, 0x06, 0x00, 0x00, 
};

const unsigned char *player_bitmaps[] = {
  playerImg_bitmap, playerKick_bitmap, playerhitFace_bitmap
};


//shrimp sprites 8x8 used for ball
const unsigned char PROGMEM shrimp00_bitmap[] =
{
  //    #### 
  //  ##  # #
  //  #     #
  // ## #### 
  // ####    
  //  ##     
  //  ##     
  //   ##    
  0x18, 0x7E, 0xF2, 0x99, 0x09, 0x0B, 0x09, 0x06, 
};

const unsigned char PROGMEM shrimp01_bitmap[] =
{
  //    ##   
  //  ###### 
  // ####  # 
  // #  ##  #
  //     #  #
  //     # ##
  //     #  #
  //      ## 
  0x0C, 0x06, 0x06, 0x0F, 0x7B, 0x82, 0xA6, 0x78, 
};

const unsigned char PROGMEM shrimp02_bitmap[] =
{
  //     ##  
  //      ## 
  //      ## 
  //     ####
  //  #### ##
  // #     # 
  // # #  ## 
  //  ####   
  0x60, 0x90, 0xD0, 0x90, 0x99, 0x4F, 0x7E, 0x18, 
};

const unsigned char PROGMEM shrimp03_bitmap[] =
{
  //  ##     
  // #  #    
  // ## #    
  // #  #    
  // #  ##  #
  //  #  ####
  //  ###### 
  //    ##   
  0x1E, 0x65, 0x41, 0xDE, 0xF0, 0x60, 0x60, 0x30, 
};

const unsigned char *shrimp_bitmaps[] = {
  shrimp00_bitmap,shrimp01_bitmap,shrimp02_bitmap,shrimp03_bitmap
};


