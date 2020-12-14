/**
 * @file lv_arc.h
 *
 */

#ifndef LV_ARC_H
#define LV_ARC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"

#if LV_USE_ARC != 0

#include "../lv_core/lv_obj.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_ARC_TYPE_NORMAL,
    LV_ARC_TYPE_SYMMETRIC,
    LV_ARC_TYPE_REVERSE
};
typedef uint8_t lv_arc_type_t;



LV_CLASS_DECLARE_START(lv_arc, lv_obj);

#define _lv_arc_constructor   void (*constructor)(struct _lv_obj_t * obj, struct _lv_obj_t * parent, const struct _lv_obj_t * copy)

#define _lv_arc_data             \
  _lv_obj_data                  \
    uint16_t angle_ofs;    \
    uint16_t indic_angle_start;   \
    uint16_t indic_angle_end;     \
    uint16_t bg_angle_start;    \
    uint16_t bg_angle_end;      \
    lv_style_list_t style_arc;  \
    lv_style_list_t style_knob; /* Style of the knob */     \
    int16_t value; /*Current value of the arc*/ \
    int16_t min_value; /*Minimum value of the arc*/ \
    int16_t max_value; /*Maximum value of the arc*/ \
    uint16_t dragging    : 1;       \
    uint16_t type        : 2;       \
    uint16_t adjustable  : 1;       \
    uint16_t min_close   : 1;  /*1: the last pressed angle was closer to minimum end*/ \
    uint16_t chg_rate; /*Drag angle rate of change of the arc (degrees/sec)*/ \
    uint32_t last_tick; /*Last dragging event timestamp of the arc*/ \
    int16_t last_angle; /*Last dragging angle of the arc*/

#define _lv_arc_class_dsc        \
  _lv_obj_class_dsc              \

LV_CLASS_DECLARE_END(lv_arc, lv_obj);

extern lv_arc_class_t lv_arc;



/*Parts of the arc*/
enum {
    LV_ARC_PART_BG = LV_OBJ_PART_MAIN,
    LV_ARC_PART_INDIC,
    LV_ARC_PART_KNOB,
    _LV_ARC_PART_VIRTUAL_LAST,
};
typedef uint8_t lv_arc_part_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a arc objects
 * @param par pointer to an object, it will be the parent of the new arc
 * @param copy pointer to a arc object, if not NULL then the new object will be copied from it
 * @return pointer to the created arc
 */
lv_obj_t * lv_arc_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the start angle of an arc. 0 deg: right, 90 bottom, etc.
 * @param arc pointer to an arc object
 * @param start the start angle
 */
void lv_arc_set_start_angle(lv_obj_t * arc, uint16_t start);

/**
 * Set the start angle of an arc. 0 deg: right, 90 bottom, etc.
 * @param arc pointer to an arc object
 * @param end the end angle
 */
void lv_arc_set_end_angle(lv_obj_t * arc, uint16_t end);

/**
 * Set the start and end angles
 * @param arc pointer to an arc object
 * @param start the start angle
 * @param end the end angle
 */
void lv_arc_set_angles(lv_obj_t * arc, uint16_t start, uint16_t end);

/**
 * Set the start angle of an arc background. 0 deg: right, 90 bottom, etc.
 * @param arc pointer to an arc object
 * @param start the start angle
 */
void lv_arc_set_bg_start_angle(lv_obj_t * arc, uint16_t start);

/**
 * Set the start angle of an arc background. 0 deg: right, 90 bottom etc.
 * @param arc pointer to an arc object
 * @param end the end angle
 */
void lv_arc_set_bg_end_angle(lv_obj_t * arc, uint16_t end);

/**
 * Set the start and end angles of the arc background
 * @param arc pointer to an arc object
 * @param start the start angle
 * @param end the end angle
 */
void lv_arc_set_bg_angles(lv_obj_t * arc, uint16_t start, uint16_t end);

/**
 * Set the rotation for the whole arc
 * @param arc pointer to an arc object
 * @param rotation_angle rotation angle
 */
void lv_arc_set_angle_ofs(lv_obj_t * arc, uint16_t rotation_angle);


/**
 * Set the type of arc.
 * @param arc pointer to arc object
 * @param type arc type
 */
void lv_arc_set_type(lv_obj_t * arc, lv_arc_type_t type);

/**
 * Set a new value on the arc
 * @param arc pointer to a arc object
 * @param value new value
 */
void lv_arc_set_value(lv_obj_t * arc, int16_t value);

/**
 * Set minimum and the maximum values of a arc
 * @param arc pointer to the arc object
 * @param min minimum value
 * @param max maximum value
 */
void lv_arc_set_range(lv_obj_t * arc, int16_t min, int16_t max);

/**
 * Set the threshold of arc knob increments
 * position.
 * @param arc pointer to a arc object
 * @param threshold increment threshold
 */
void lv_arc_set_chg_rate(lv_obj_t * arc, uint16_t threshold);

/**
 * Set whether the arc is adjustable.
 * @param arc pointer to a arc object
 * @param adjustable whether the arc has a knob that can be dragged
 */
void lv_arc_set_adjustable(lv_obj_t * arc, bool adjustable);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the start angle of an arc.
 * @param arc pointer to an arc object
 * @return the start angle [0..360]
 */
static inline uint16_t lv_arc_get_angle_start(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->indic_angle_start;
}

/**
 * Get the end angle of an arc.
 * @param arc pointer to an arc object
 * @return the end angle [0..360]
 */
static inline uint16_t lv_arc_get_angle_end(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->indic_angle_end;
}

/**
 * Get the start angle of an arc background.
 * @param arc pointer to an arc object
 * @return the start angle [0..360]
 */
static inline uint16_t lv_arc_get_bg_angle_start(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->bg_angle_start;
}

/**
 * Get the end angle of an arc background.
 * @param arc pointer to an arc object
 * @return the end angle [0..360]
 */
static inline uint16_t lv_arc_get_bg_angle_end(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->bg_angle_end;
}


/**
 * Get the value of a arc
 * @param arc pointer to a arc object
 * @return the value of the arc
 */
static inline int16_t lv_arc_get_value(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->value;
}

/**
 * Get the minimum value of a arc
 * @param arc pointer to a arc object
 * @return the minimum value of the arc
 */
static inline int16_t lv_arc_get_min_value(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->min_value;
}

/**
 * Get the maximum value of a arc
 * @param arc pointer to a arc object
 * @return the maximum value of the arc
 */
static inline int16_t lv_arc_get_max_value(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->max_value;
}

/**
 * Get whether the arc is type or not.
 * @param arc pointer to a arc object
 * @return arc type
 */
static inline lv_arc_type_t lv_arc_get_type(const lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->type;
}

/**
 * Get whether the arc is adjustable.
 * @param arc pointer to a arc object
 * @return whether the arc has a knob that can be dragged
 */
static inline bool lv_arc_get_adjustable(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, LV_OBJX_NAME);
    return ((lv_arc_t*) obj)->adjustable;
}

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ARC*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ARC_H*/
