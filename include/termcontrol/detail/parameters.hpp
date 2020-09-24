#pragma once
#include <cstdint>
#include <type_traits>

#include "control_sequence_definition.hpp"
#include "formatted_size.hpp"
#include "bitmask_operators.hpp"

namespace termcontrol {

/// Parameters for EL - ERASE IN LINE
enum class erase_line_mode : std::uint8_t {
    after  = 0,            ///< clear from cursor to end of the line
    before = 1,            ///< clear from cursor to beginning of the line
    full   = 2,            ///< clear entire line
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(erase_line_mode, 1);


/// Parameters for ED - ERASE IN PAGE
enum class erase_page_mode : std::uint8_t {
    below = 0,             ///< clear from cursor to end of page.
    above = 1,             ///< clear from start of the page up to and including cursor
    full = 2,              ///< clear entire screen (and moves cursor to upper left)
    full_scrollback = 3    ///< clear entire screen and delete all lines saved in the scrollback buffer
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(erase_page_mode, 1);


/// Parameters for EF - ERASE IN FIELD
enum class erase_in_field_mode : std::uint8_t {
    after  = 0,            ///< clear from cursor to end of the field
    before = 1,            ///< clear from the beginning of the field up to and including cursor
    full   = 2,            ///< clear entire field
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(erase_in_field_mode, 1);


/// Parameters for EA - ERASE IN AREA
/// Dependent on DEVICE COMPONENT SELECT MODE (DCSM) to determine
/// if the area is a PRESENTATION area or a DATA area
enum class erase_in_area_mode : std::uint8_t {
    after  = 0,             ///< clear from position to end of active area
    before = 1,             ///< clear from start of area up to and including currrent position
    full   = 2,             ///< clear all positions of the active area
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(erase_in_area_mode, 1);


/// Parameters for CRC - CURSOR TABULATION CONTROL
enum class cursor_tabulation_control_mode : std::uint8_t {
    set_character_tab        = 1 << 0,     ///< 0: set a horizontal tab at the current position
    set_line_tab             = 1 << 1,     ///< 1: set a vertical tab at the current position
    clear_character_tab      = 1 << 2,     ///< 2: clear a horizontal tab at the current position
    clear_line_tab           = 1 << 3,     ///< 3: clear a vertical tab at the current position
    clear_character_tab_line = 1 << 4,     ///< 4: clear all horizontal tabs in the active line
    clear_character_tab_all  = 1 << 5,     ///< 5: clear all horizontal tabs
    clear_line_tab_all       = 1 << 6,     ///< 6: clear all vertical_tabs
};

TERMCONTROL_ENABLE_BITMASK_OPERATORS(cursor_tabulation_control_mode);
// max two combined parameters + seperator
TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(cursor_tabulation_control_mode, 3);


/// Parameters for TBC - TABULATION CLEAR
enum class tabulation_clear_mode : std::uint8_t
{
    character              = 0,         ///< clear character tab stop at current position
    line                   = 1,         ///< clear line tab stop at current position
    character_all_in_line  = 2,         ///< clear all character tab stops in active line
    character_all          = 3,         ///< clear all character tab stops
    line_all               = 4,         ///< clear all line tab stops
    all                    = 5,         ///< clear all character and line tab stops
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(tabulation_clear_mode, 1);


/// Parameters for DAQ - DEFINE AREA QUALIFICATION
enum class area_qualification : std::uint16_t
{
    unprotected_unguarded   = 0,        ///< 0:  unprotected and unguarded
    protected_guarded       = 1,        ///< 1:  protected and guarded
    graphic                 = 1 << 1,   ///< 2:  graphic character input
    numeric                 = 1 << 2,   ///< 3:  numeric input
    alphabetic              = 1 << 3,   ///< 4:  alphabetic input
    aligned_end             = 1 << 4,   ///< 5:  input aligned on the last character position of the qualified area
    filled_zero             = 1 << 5,   ///< 6:  fill with ZEROs
    set_character_tab       = 1 << 6,   ///< 7:  set a character tabulation stop at the active presentation position
                                        ///      (the first character position of the qualified area) to indicate the
                                        ///      beginning of a field
    protected_unguarded     = 1 << 7,   ///< 8:  protected and unguarded
    filled_space            = 1 << 8,   ///< 9:  fill with spaces
    align_start             = 1 << 9,   ///< 10: input aligned on the first character position of the qualified area
    reverse_character_input = 1 << 10,  ///< 11: the order of the character positions in the input field is
                                        ///      reversed, i.e. the last position in each line becomes the first
                                        ///      and vice versa; input begins at the new first position.
};

TERMCONTROL_ENABLE_BITMASK_OPERATORS(area_qualification);
TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(area_qualification, 25);


/// Parameters for SM - SET MODE
enum class mode : std::uint8_t
{
    guarded_area_transfer         = 1,       ///< GUARDED AREA TRANSFER MODE (GATM)
    keyboard_action               = 2,       ///< KEYBOARD ACTION MODE (KAM)
    control_representation        = 3,       ///< CONTROL REPRESENTATION MODE (CRM)
    insertion_replacement         = 4,       ///< INSERTION REPLACEMENT MODE (IRM)
    status_report_transfer        = 5,       ///< STATUS REPORT TRANSFER MODE (SRTM)
    erasure                       = 6,       ///< ERASURE MODE (ERM)
    line_editing                  = 7,       ///< LINE EDITING MODE (VEM)
    bidirectional_support         = 8,       ///< BI-DIRECTIONAL SUPPORT MODE (BDSM)
    device_component_select       = 9,       ///< DEVICE COMPONENT SELECT MODE (DCSM)
    character_editing             = 10,      ///< CHARACTER EDITING MODE (HEM)
    positioning_unit              = 11,      ///< POSITIONING UNIT MODE (PUM)
    send_receive                  = 12,      ///< SEND/RECEIVE MODE (SRM)
    format_effector_action        = 13,      ///< FORMAT EFFECTOR ACTION MODE (FEAM)
    format_effector_transfer      = 14,      ///< FORMAT EFFECTOR TRANSFER MODE (FETM)
    multiple_area_transfer        = 15,      ///< MULTIPLE AREA TRANSFER MODE (MATM)
    transfer_termination          = 16,      ///< TRANSFER TERMINATION MODE (TTM)
    selected_area_transfer        = 17,      ///< SELECTED AREA TRANSFER MODE (SATM)
    tabulation_stop               = 18,      ///< TABULATION STOP MODE (TSM)
    graphic_rendition_combination = 21,      ///< GRAPHIC RENDITION COMBINATION (GRCM)
    zero_default_mode             = 22,      ///< ZERO DEFAULT MODE (ZDM)
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(mode, 2);

/// DEC private parameters for SM - SET MODE.
enum class dec_mode : std::uint16_t {
    alternate_prefix    = 1,          ///< Send an ESC O prefix, rather than ESC [.
    reverse_video       = 5,          ///< Reverse video mode.
    relative_adressing  = 6,          ///< Cursor addressing relative to the current scrolling region.
    autowrap            = 7,          ///< Wrap text exceeding terminal width (Default: On).
    keyboard_autorepeat = 8,          ///< (default on): Make cursor visible.
    x10_mouse_reporting = 9,          ///< (default off): Set reporting mode to 1.
    cursor_visible      = 25,         ///< (default on): Make cursor visible.
    x11_mouse_reporting = 1000        ///< (default off): Set reporting mode to 2
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(dec_mode, 4);

/// Other Set Graphics Rendition attributes that are not colors or emphasis types.
enum class graphics_rendition_attributes { };

enum class emphasis : std::uint16_t {
    reset            = 1,
    bold             = 1 << 1,
    italic           = 1 << 2,
    underline        = 1 << 3,
    striketrough     = 1 << 4,
    overline         = 1 << 5,
    double_underline = 1 << 6,
    blinking         = 1 << 7,
    reverse          = 1 << 8
};

TERMCONTROL_DEFINE_MAX_FORMATTED_SIZE(emphasis, 18);
TERMCONTROL_ENABLE_BITMASK_OPERATORS(emphasis);

} // namespace termcontrol
