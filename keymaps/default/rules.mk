OLED_ENABLE = yes
OLED_DRIVER = SSD1306      # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
COMBO_ENABLE = yes
RGB_MATRIX_ENABLE = no     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
SRC += features/layer_lock.c
