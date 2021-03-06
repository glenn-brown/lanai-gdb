/* THIS FILE IS GENERATED.  Original: i386.xml */

#include "defs.h"
#include "osabi.h"
#include "target-descriptions.h"

struct target_desc *tdesc_i386;
static void
initialize_tdesc_i386 (void)
{
  struct target_desc *result = allocate_target_description ();
  struct tdesc_feature *feature;
  struct tdesc_type *field_type, *type;

  set_tdesc_architecture (result, bfd_scan_arch ("i386"));

  feature = tdesc_create_feature (result, "org.gnu.gdb.i386.core");
  tdesc_create_reg (feature, "eax", 0, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "ecx", 1, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "edx", 2, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "ebx", 3, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "esp", 4, 1, NULL, 32, "data_ptr");
  tdesc_create_reg (feature, "ebp", 5, 1, NULL, 32, "data_ptr");
  tdesc_create_reg (feature, "esi", 6, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "edi", 7, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "eip", 8, 1, NULL, 32, "code_ptr");
  tdesc_create_reg (feature, "eflags", 9, 1, NULL, 32, "i386_eflags");
  tdesc_create_reg (feature, "cs", 10, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "ss", 11, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "ds", 12, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "es", 13, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "fs", 14, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "gs", 15, 1, NULL, 32, "int32");
  tdesc_create_reg (feature, "st0", 16, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st1", 17, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st2", 18, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st3", 19, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st4", 20, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st5", 21, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st6", 22, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "st7", 23, 1, NULL, 80, "i387_ext");
  tdesc_create_reg (feature, "fctrl", 24, 1, "float", 32, "int");
  tdesc_create_reg (feature, "fstat", 25, 1, "float", 32, "int");
  tdesc_create_reg (feature, "ftag", 26, 1, "float", 32, "int");
  tdesc_create_reg (feature, "fiseg", 27, 1, "float", 32, "int");
  tdesc_create_reg (feature, "fioff", 28, 1, "float", 32, "int");
  tdesc_create_reg (feature, "foseg", 29, 1, "float", 32, "int");
  tdesc_create_reg (feature, "fooff", 30, 1, "float", 32, "int");
  tdesc_create_reg (feature, "fop", 31, 1, "float", 32, "int");

  feature = tdesc_create_feature (result, "org.gnu.gdb.i386.sse");
  field_type = tdesc_named_type (feature, "ieee_single");
  tdesc_create_vector (feature, "v4f", field_type, 4);

  field_type = tdesc_named_type (feature, "ieee_double");
  tdesc_create_vector (feature, "v2d", field_type, 2);

  field_type = tdesc_named_type (feature, "int8");
  tdesc_create_vector (feature, "v16i8", field_type, 16);

  field_type = tdesc_named_type (feature, "int16");
  tdesc_create_vector (feature, "v8i16", field_type, 8);

  field_type = tdesc_named_type (feature, "int32");
  tdesc_create_vector (feature, "v4i32", field_type, 4);

  field_type = tdesc_named_type (feature, "int64");
  tdesc_create_vector (feature, "v2i64", field_type, 2);

  type = tdesc_create_union (feature, "vec128");
  field_type = tdesc_named_type (feature, "v4f");
  tdesc_add_field (type, "v4_float", field_type);
  field_type = tdesc_named_type (feature, "v2d");
  tdesc_add_field (type, "v2_double", field_type);
  field_type = tdesc_named_type (feature, "v16i8");
  tdesc_add_field (type, "v16_int8", field_type);
  field_type = tdesc_named_type (feature, "v8i16");
  tdesc_add_field (type, "v8_int16", field_type);
  field_type = tdesc_named_type (feature, "v4i32");
  tdesc_add_field (type, "v4_int32", field_type);
  field_type = tdesc_named_type (feature, "v2i64");
  tdesc_add_field (type, "v2_int64", field_type);
  field_type = tdesc_named_type (feature, "uint128");
  tdesc_add_field (type, "uint128", field_type);

  tdesc_create_reg (feature, "xmm0", 32, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm1", 33, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm2", 34, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm3", 35, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm4", 36, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm5", 37, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm6", 38, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "xmm7", 39, 1, NULL, 128, "vec128");
  tdesc_create_reg (feature, "mxcsr", 40, 1, "vector", 32, "i386_mxcsr");

  tdesc_i386 = result;
}
