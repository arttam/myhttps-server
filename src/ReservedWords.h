#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

// clang-format off
const std::unordered_map<std::string, std::unordered_set<std::string>> CPPFormatting{
    {{"cppreserved"},
     {"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break",
      "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const", "consteval", "constexpr", "constinit", "const_cast",
      "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
      "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
      "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "reflexpr", "register", "reinterpret_cast", "requires", "return", "short",
      "signed", "sizeof", "size_t", "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
      "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", 
      "xor_eq"}},
    {{"stlnamespaces"}, 
     {"std", "chrono", "exprerimental", "literals", "chrono_literals", "string_literals", "execution", "filesystem" }},
    {{"stlconstant"},
     {"badbit", "cerr", "cin", "clog", "cout", "digits", "digits10", "eofbit", "failbit", "goodbit", "has_denorm", "has_denorm_loss", "has_infinity",
      "has_quiet_NaN", "has_signaling_NaN", "is_bounded", "is_exact", "is_iec559", "is_integer", "is_modulo", "is_signed", "is_specialized", "max_digits10",
      "max_exponent", "max_exponent10", "min_exponent", "min_exponent10", "nothrow", "npos", "radix", "round_style", "tinyness_before", "traps", "wcerr",
      "wcin", "wclog", "wcout", "MB_LEN_MAX", "MB_CUR_MAX", "__STDC_UTF_16__", "__STDC_UTF_32__", "WEOF", "WCHAR_MIN", "WCHAR_MAX", "nullptr",
      "ATOMIC_FLAG_INIT", "_1 _2 _3 _4 _5 _6 _7 _8 _9", "max_digits10", "allocator_arg", "defer_lock try_to_lock adopt_lock", "HUGE_VALF", "HUGE_VALL",
      "INFINITY", "NAN", "math_errhandling", "MATH_ERRNO", "MATH_ERREXCEPT", "FP_NORMAL", "FP_SUBNORMAL", "FP_ZERO", "FP_INFINITY", "FP_NAN", "FLT_EVAL_METHOD",
      "piecewise_construct", "is_always_lock_free", "seq par par_unseq", "available", "hardware_destructive_interference_size",
      "hardware_constructive_interference_size", "nullopt", "tuple_size_v", "alignment_of_v", "rank_v", "extent_v", "variant_size_v", "variant_npos",
      "dynamic_extent"}},
    {{"stlexception"}, {"bad_alloc",           "bad_array_new_length", "bad_exception",
                         "bad_typeid bad_cast", "domain_error",         "exception",
                         "invalid_argument",    "length_error",         "logic_error",
                         "out_of_range",        "overflow_error",       "range_error",
                         "runtime_error",       "underflow_error",      "bad_function_call",
                         "future_error",        "bad_weak_ptr",         "bad_array_new_length",
                         "regex_error",         "bad_any_cast",         "filesystem_error",
                         "bad_optional_access", "bad_variant_access"}},
    {{"stlfunction"},
     {"abort", "abs", "accumulate", "acos", "adjacent_difference", "adjacent_find", "adjacent_find_if", "advance", "any", "append",
      "arg", "asctime", "asin", "assert", "assign", "at", "atan", "atan2", "atexit", "atof", "atoi", "atol", "atoll", "back", "back_inserter",
      "bad", "beg", "begin", "binary_compose", "binary_negate", "binary_search", "bind1st", "bind2nd", "binder1st", "binder2nd", "bsearch", "calloc",
      "capacity", "ceil", "clear", "clearerr", "clock", "close", "compare", "conj", "construct", "copy", "copy_backward", "cos", "cosh", "count",
      "count_if", "c_str", "ctime", "data", "denorm_min", "destroy", "difftime", "distance", "div", "empty", "end", "eof", "epsilon", "equal", "equal_range",
      "erase", "exit", "exp", "fabs", "fail", "failure", "fclose", "feof", "ferror", "fflush", "fgetc", "fgetpos", "fgets", "fill", "fill_n", "find",
      "find_end", "find_first_not_of", "find_first_of", "find_if", "find_last_not_of", "find_last_of", "first", "flags", "flip", "floor", "flush", "fmod",
      "fopen", "for_each", "fprintf", "fputc", "fputs", "fread", "free", "freopen", "frexp", "front", "fscanf", "fseek", "fsetpos", "ftell", "fwide", "fwprintf",
      "fwrite", "fwscanf", "gcount", "generate", "generate_n", "get", "get_allocator", "getc", "getchar", "getenv", "getline", "gets", "get_temporary_buffer",
      "gmtime", "good", "ignore", "imag", "in", "includes", "infinity", "inner_product", "inplace_merge", "insert", "inserter", "ios", "ios_base", "iostate",
      "iota", "isalnum", "isalpha", "iscntrl", "isdigit", "isgraph", "is_heap", "islower", "is_open", "isprint", "ispunct", "isspace", "isupper", "isxdigit",
      "iterator_category", "iter_swap", "jmp_buf", "key_comp", "labs", "ldexp", "ldiv", "length", "lexicographical_compare", "lexicographical_compare_3way",
      "llabs", "lldiv", "localtime", "log", "log10", "longjmp", "lower_bound", "make_heap", "make_pair", "malloc", "max", "max_element", "max_size",
      "memchr", "memcpy", "mem_fun", "mem_fun_ref", "memmove", "memset", "merge", "min", "min_element", "mismatch", "mktime", "modf", "next_permutation",
      "none", "norm", "not1", "not2", "nth_element", "open", "partial_sort", "partial_sort_copy", "partial_sum", "partition", "peek", "perror", "polar",
      "pop", "pop_back", "pop_front", "pop_heap", "pow", "power", "precision", "prev_permutation", "printf", "ptr_fun", "push", "push_back", "push_front",
      "push_heap", "put", "putback", "putc", "putchar", "puts", "qsort", "quiet_NaN", "raise", "rand", "random_sample", "random_sample_n", "random_shuffle",
      "rbegin", "rdbuf", "rdstate", "read", "real", "realloc", "remove", "remove_copy", "remove_copy_if", "remove_if", "rename", "rend", "replace",
      "replace_copy", "replace_copy_if", "replace_if", "reserve", "reset", "resize", "return_temporary_buffer", "reverse", "reverse_copy", "rewind",
      "rfind", "rotate", "rotate_copy", "round_error", "scanf", "search", "search_n", "second", "seekg", "seekp", "setbuf", "set_difference", "setf",
      "set_intersection", "setjmp", "setlocale", "set_new_handler", "set_symmetric_difference", "set_union", "setvbuf", "signal", "signaling_NaN", "sin",
      "sinh", "size", "sort", "sort_heap", "splice", "sprintf", "sqrt", "srand", "sscanf", "stable_partition", "stable_sort", "str", "strcat", "strchr",
      "strcmp", "strcoll", "strcpy", "strcspn", "strerror", "strftime", "string", "strlen", "strncat", "strncmp", "strncpy", "strpbrk", "strrchr", "strspn",
      "strstr", "strtod", "strtof", "strtok", "strtol", "strtold", "strtoll", "strtoul", "strxfrm", "substr", "swap", "swap_ranges", "swprintf", "swscanf",
      "sync_with_stdio", "system", "tan", "tanh", "tellg", "tellp", "test", "time", "tmpfile", "tmpnam", "tolower", "top", "to_string", "to_ulong",
      "toupper", "to_wstring", "transform", "unary_compose", "unget", "ungetc", "uninitialized_copy", "uninitialized_copy_n", "uninitialized_fill",
      "uninitialized_fill_n", "unique", "unique_copy", "unsetf", "upper_bound", "va_arg", "va_copy", "va_end", "value_comp", "va_start", "vfprintf",
      "vfwprintf", "vprintf", "vsprintf", "vswprintf", "vwprintf", "width", "wprintf", "write", "wscanf", "mblen", "mbtowc", "wctomb", "mbstowcs",
      "wcstombs", "mbsinit", "btowc", "wctob", "mbrlen", "mbrtowc", "wcrtomb", "mbsrtowcs", "wcsrtombs", "iswalnum", "iswalpha", "iswlower", "iswupper",
      "iswdigit", "iswxdigit", "iswcntrl", "iswgraph", "iswspace", "iswprint", "iswpunct", "iswctype", "wctype", "towlower", "towupper", "towctrans", "wctrans",
      "wcstol", "wcstoll", "wcstoul", "wcstoull", "wcstof", "wcstod", "wcstold", "wcscpy", "wcsncpy", "wcscat", "wcsncat", "wcsxfrm", "wcslen", "wcscmp",
      "wcsncmp", "wcscoll", "wcschr", "wcsrchr", "wcsspn", "wcscspn", "wcspbrk", "wcsstr", "wcstok", "wmemcpy", "wmemmove", "wmemcmp", "wmemchr", "wmemset",
      "use_facet", "has_facet", "isspace isblank iscntrl isupper islower isalpha", "isdigit ispunct isxdigit isalnum isprint isgraph", "cbegin cend",
      "crbegin crend", "shrink_to_fit", "emplace", "emplace_back", "emplace_front", "emplace_hint", "all_of any_of none_of", "find_if_not", "copy_if",
      "copy_n", "move", "move_backward", "shuffle", "is_partitioned", "partition_copy", "partition_point", "is_sorted", "is_sorted_until", "is_heap",
      "is_heap_until", "minmax", "minmax_element", "is_permutation", "itoa", "is_lock_free", "compare_exchange_weak", "compare_exchange_strong",
      "fetch_add", "fetch_sub", "fetch_and", "fetch_or", "fetch_xor", "atomic_is_lock_free", "atomic_store", "atomic_store_explicit", "atomic_load",
      "atomic_load_explicit", "atomic_exchange", "atomic_exchange_explicit", "atomic_compare_exchange_weak", "atomic_compare_exchange_weak_explicit",
      "atomic_compare_exchange_strong", "atomic_compare_exchange_strong_explicit", "atomic_fetch_add", "atomic_fetch_add_explicit", "atomic_fetch_sub",
      "atomic_fetch_sub_explicit", "atomic_fetch_and", "atomic_fetch_and_explicit", "atomic_fetch_or", "atomic_fetch_or_explicit", "atomic_fetch_xor",
      "atomic_fetch_xor_explicit", "atomic_flag_test_and_set", "atomic_flag_test_and_set_explicit", "atomic_flag_clear", "atomic_flag_clear_explicit",
      "atomic_init", "ATOMIC_VAR_INIT", "kill_dependency", "atomic_thread_fence", "atomic_signal_fence", "exchange", "store", "load", "to_ullong", "all",
      "strtoimax", "strtoumax", "wcstoimax", "wcstoumax", "time_since_epoch", "to_time_t", "from_time_t", "zero", "now", "proj", "notify_all", "notify_one",
      "quick_exit", "_Exit", "at_quick_exit", "mbrtoc16", "c16rtomb", "mbrtoc32", "c32rtomb", "get_terminate", "make_exception_ptr", "current_exception",
      "rethrow_exception", "throw_with_nested", "rethrow_if_nested", "rethrow_nested", "before_begin", "cbefore_begin", "insert_after", "emplace_after",
      "erase_after", "splice_after", "bind", "mem_fn", "ref cref", "get_future", "set_value", "set_value_at_thread_exit", "set_exception",
      "set_exception_at_thread_exit", "wait_for", "wait_until", "future_category", "make_error_code", "make_error_condition", "make_ready_at_thread_exit",
      "async", "share", "valid", "wait", "iostream_category", "vscanf vfscanf vsscanf", "snprintf vsnprintf", "vwscanf vfwscanf vswscanf",
      "make_move_iterator", "next prev", "lowest", "isblank", "iswblank", "make_shared", "declare_reachable", "undeclare_reachable", "declare_no_pointers",
      "undeclare_no_pointers", "get_pointer_safety", "addressof", "allocate_shared", "get_deleter", "align", "try_lock lock unlock try_lock_for try_lock_until",
      "call_once", "owns_lock", "notify_all_at_thread_exit", "release", "mutex", "get_new_handler", "imaxabs", "imaxdiv", "remainder", "remquo",
      "fma", "fmax", "fmin", "fdim", "nan", "nanf", "nanl", "exp2", "expm1", "log1p", "log2", "cbrt", "hypot", "asinh", "acosh", "atanh", "erf",
      "erfc", "lgamma", "tgamma", "trunc", "round", "lround", "llround", "nearbyint", "rint", "lrint", "llrint", "scalbn", "scalbln", "ilogb",
      "logb", "nextafter", "nexttoward", "copysign", "fpclassify", "isfinite", "isinf", "isnan", "isnormal", "signbit", "generate_canonical",
      "stoi", "stol", "stoll", "stoul", "stoull", "stof", "stod", "stold", "default_error_condition", "generic_category", "system_category",
      "code", "category", "message", "equivalent", "get_id", "sleep_for", "sleep_until", "joinable", "native_handle", "hardware_concurrency", "yield",
      "join", "detach", "make_tuple", "tie", "forward_as_tuple", "tuple_cat", "bucket_count", "max_bucket_count", "bucket_size", "bucket", "load_factor",
      "max_load_factor", "rehash", "reserve", "hash_function", "key_eq", "declval", "forward", "move_if_noexcept", "make_reverse_iterator", "make_unique",
      "lock_shared", "unlock_shared", "try_lock_shared", "try_lock_shared_for", "try_lock_shared_until", "clamp", "for_each_n", "make_any", "to_array",
      "make_array", 
      "assoc_laguerre", "assoc_laguerref", "assoc_laguerrel", "assoc_legendre", "assoc_legendref", "assoc_legendrel", "beta", "betaf", "betal",
      "comp_ellint_1", "comp_ellint_1f", "comp_ellint_1l", "comp_ellint_2", "comp_ellint_2f", "comp_ellint_2l", "comp_ellint_3", 
      "comp_ellint_3f", "comp_ellint_3l", "cyl_bessel_i", "cyl_bessel_if", "cyl_bessel_il", "cyl_bessel_j", "cyl_bessel_jf", "cyl_bessel_jl", 
      "cyl_bessel_k", "cyl_bessel_kf", "cyl_bessel_kl", "cyl_neumann", "cyl_neumannf", "cyl_neumannl", "ellint_1", "ellint_1f", "ellint_1l", 
      "ellint_2", "ellint_2f", "ellint_2l", "ellint_3", "ellint_3f", "ellint_3l",
      "expint", "expintf", "expintl", "hermite", "hermitef", "hermitel", "legendre", "legendrefl", "egendrel", "laguerre", "laguerref", "laguerrel",
      "riemann_zeta", "riemann_zetaf", "riemann_zetal", "sph_bessel", "sph_besself", "sph_bessell", "sph_legendre", "sph_legendref", "sph_legendrel",
      "sph_neumann", "sph_neumannf", "sph_neumannl",
      "aligned_alloc", "uncaught_exceptions", "concat", "make_preferred", "remove_filename", "replace_filename", "replace_extension", "native",
      "string_type", "wstring", "u8string", "u16string", "u32string", "generic_string", "generic_wstring", "generic_u8string", "generic_u16string",
      "generic_u32string", "lexically_normal", "lexically_relative", "lexically_proximate", "root_name", "root_directory", "root_path", "relative_path",
      "parent_path", "filename", "stem", "extension", "has_root_name", "has_root_directory", "has_root_path", "has_relative_path", "has_parent_path",
      "has_filename", "has_stem", "has_extension", "is_absolute", "is_relative", "hash_value", "u8path", "path1", "path2", "path", "status",
      "symlink_status", "options", "depth", "recursive_pending", "disable_recursive_pending", "type", "permissions", "absolute", "system_complete",
      "canonical", "weakly_canonical", "relative", "proximate", "copy_file", "copy_symlink", "create_directory", "create_directories", "create_hard_link",
      "create_symlink", "create_directory_symlink", "current_path", "exists", "file_size", "hard_link_count", "last_write_time", "read_symlink",
      "remove_all", "resize_file", "space", "temp_directory_path", "is_block_file", "is_character_file", "is_directory", "is_fifo", "is_other",
      "is_regular_file", "is_socket", "is_symlink", "status_known", "is_empty", "not_fn", "make_default_searcher", "make_boyer_moore_searcher",
      "make_boyer_moore_horspool_searcher", "invoke", "uninitialized_move", "uninitialized_move_n", "uninitialized_default_construct",
      "uninitialized_default_construct_n", "uninitialized_value_construct", "uninitialized_value_construct_n", "destroy_at",
      "destroy_n", "upstream_resource", "get_default_resource", "new_default_resource", "set_default_resource", "null_memory_resource", "allocate",
      "deallocate", "construct", "destruct", "resource", "select_on_container_copy_construction", "do_allocate", "do_deallocate", "do_is_equal",
      "launder", "gcd", "lcm", "exclusive_scan", "inclusive_scan", "transform_reduce", "transform_exclusive_scan", "transform_inclusive_scan",
      "reduce", "make_optional", "value_or", "has_value", "value", "remove_prefix", "remove_suffix", "make_from_tuple", "apply",
      "try_emplace", "insert_or_assign", "extract", "in_place", "as_const", "valueless_by_exception", "holds_alternative", "get_if", "visit",
      "index", "shift_left", "shift_right", "lexicographical_compare_three_way", "ispow2", "ceil2", "floor2", "log2p1", "rotl", "rotr", "countl_zero",
      "countl_one", "countr_zero", "countr_one", "popcount", "is_eq", "is_neq", "is_lt", "is_lteq", "is_gt", "is_gteq", "to_address", "assume_aligned",
      "make_unique_default_init", "allocate_shared_default_init", "as_bytes", "as_writable_bytes", "is_constant_evaluated", "is_pointer_interconvertible",
      "is_corresponding_member"}},
    {{"stlfunctional"},{
        "binary_function", "binary_negate", "bit_and", "bit_not", "bit_or", "bit_xor", "divides", "equal_to", "greater", "greater_equal",
        "less", "less_equal", "logical_and", "logical_not", "logical_or", "minus", "modulus", "multiplies", "negate", "not_equal_to",
        "plus", "unary_function", "unary_negate" }},
    {{"stltype"}, {
        "numeric_limits", "allocator", "auto_ptr", "basic_filebuf", "basic_fstream", "basic_ifstream", "basic_iostream", "basic_istream", "basic_istringstream",
        "basic_ofstream", "basic_ostream", "basic_ostringstream", "basic_streambuf", "basic_string", "basic_stringbuf", "basic_stringstream", "binary_compose",
        "binder1st", "binder2nd", "bitset", "char_traits", "char_type", "const_mem_fun1_t", "const_mem_fun_ref1_t", "const_mem_fun_ref_t", "const_mem_fun_t",
        "const_pointer", "const_reference", "container_type", "deque", "difference_type", "div_t", "double_t", "filebuf", "first_type", "float_denorm_style",
        "float_round_style", "float_t", "fstream", "gslice_array", "ifstream", "imaxdiv_t", "indirect_array", "int_type", "ios_base", "iostream",
        "istream", "istringstream", "istrstream", "iterator_traits", "key_compare", "key_type", "ldiv_t", "list", "lldiv_t", "map", "mapped_type", "mask_array",
        "mem_fun1_t", "mem_fun_ref1_t", "mem_fun_ref_t", "mem_fun_t", "multimap", "multiset", "nothrow_t", "off_type", "ofstream", "ostream", "ostringstream",
        "ostrstream", "pair", "pointer", "pointer_to_binary_function", "pointer_to_unary_function", "pos_type", "priority_queue", "queue", "reference",
        "second_type", "sequence_buffer", "set", "sig_atomic_t", "size_type", "slice_array", "stack", "stream", "streambuf", "streamsize", "string",
        "stringbuf", "stringstream", "strstream", "strstreambuf", "temporary_buffer", "test_type", "time_t", "tm", "traits_type", "type_info",
        "u16string", "u32string", "unary_compose", "unary_negate", "valarray", "value_compare", "value_type", "vector", "wfilebuf", "wfstream", "wifstream",
        "wiostream", "wistream", "wistringstream", "wofstream", "wostream", "wostringstream", "wstreambuf", "wstring", "wstringbuf", "wstringstream",
        "mbstate_t", "wctrans_t", "wctype_t", "wint_t", "locale", "ctype_base", "codecvt_base", "messages_base", "time_base", "money_base", "ctype",
        "codecvt", "collate", "messages", "time_get", "time_put", "num_get", "num_put", "numpunct", "money_get", "money_put", "moneypunct",
        "ctype_byname", "codecvt_byname", "messages_byname", "collate_byname", "time_get_byname", "time_put_byname", "numpunct_byname", "moneypunct_byname",
        "cppSTLtype array", "cppSTLtype atomic", "cppSTLtype atomic_flag", "cppSTLtype atomic_bool", "cppSTLtype atomic_char", "cppSTLtype atomic_schar",
        "cppSTLtype atomic_uchar", "cppSTLtype atomic_short", "atomic_ushort", "atomic_int", "atomic_uint", "atomic_long", "atomic_ulong", "atomic_llong",
        "atomic_ullong", "atomic_char16_t", "atomic_char32_t", "atomic_wchar_t", "atomic_int_least8_t", "atomic_uint_least8_t", "atomic_int_least16_t",
        "atomic_uint_least16_t", "atomic_int_least32_t", "atomic_uint_least32_t", "atomic_int_least64_t", "atomic_uint_least64_t", "atomic_int_fast8_t",
        "atomic_uint_fast8_t", "atomic_int_fast16_t", "atomic_uint_fast16_t", "atomic_int_fast32_t", "atomic_uint_fast32_t", "atomic_int_fast64_t",
        "atomic_uint_fast64_t", "atomic_intptr_t", "atomic_uintptr_t", "atomic_size_t", "atomic_ptrdiff_t", "atomic_intmax_t", "atomic_uintmax_t",
        "memory_order_relaxed", "memory_order_consume", "memory_order_acquire", "memory_order_release", "memory_order_acq_rel", "memory_order_seq_cst",
        "duration", "system_clock", "steady_clock", "high_resolution_clock", "time_point", "nanoseconds", "microseconds", "milliseconds", "seconds",
        "minutes", "hours", "treat_as_floating_point", "duration_values", "condition_variable", "nullptr_t max_align_t", "exception_ptr", "nested_exception",
        "forward_list", "hash", "is_bind_expression", "is_placeholder", "reference_wrapper", "future", "packaged_task", "promise", "shared_future",
        "initializer_list", "wstring_convert", "wbuffer_convert", "codecvt_utf8", "codecvt_utf16", "codecvt_utf8_utf16", "codecvt_mode",
        "unique_ptr", "shared_ptr", "weak_ptr", "owner_less", "enable_shared_from_this", "default_delete", "allocator_traits", "allocator_type",
        "allocator_arg_t", "uses_allocator", "scoped_allocator_adaptor", "pointer_safety", "pointer_traits", "mutex", "timed_mutex", "recursive_mutex",
        "recursive_timed_mutex", "lock_guard", "unique_lock", "defer_lock_t", "try_to_lock_t", "adopt_lock_t", "once_flag", "condition_variable_any",
        "linear_congruential_engine", "mersenne_twister_engine", "subtract_with_carry_engine", "discard_block_engine", "independent_bits_engine",
        "shuffle_order_engine", "random_device", "default_random_engine", "minstd_rand0", "minstd_rand", "mt19937", "mt19937_64", "ranlux24_base",
        "ranlux48_base", "ranlux24", "ranlux48", "knuth_b", "uniform_int_distribution", "uniform_real_distribution", "bernoulli_distribution",
        "binomial_distribution", "negative_binomial_distribution", "geometric_distribution", "poisson_distribution", "exponential_distribution",
        "gamma_distribution", "weibull_distribution", "extreme_value_distribution", "normal_distribution", "lognormal_distribution", "chi_squared_distribution",
        "cauchy_distribution", "fisher_f_distribution", "student_t_distribution", "discrete_distribution", "piecewise_constant_distribution",
        "piecewise_linear_distribution", "seed_seq", "ratio", "yocto", "zepto", "atto", "femto", "pico", "nano", "micro", "milli",
        "centi", "deci", "deca", "hecto", "kilo", "mega", "giga", "tera", "peta", "exa", "zetta", "yotta", "ratio_add", "ratio_subtract",
        "ratio_multiply", "ratio_divide", "ratio_equal", "ratio_not_equal", "ratio_less", "ratio_less_equal", "ratio_greater", "ratio_greater_equal",
        "basic_regex", "sub_match", "match_results", "regex_traits", "regex_match", "regex_search", "regex_replace", 
        "syntax_option_type", "match_flag_type error_type", "system_error", "error_code", "error_condition", "error_category", "is_error_code_enum",
        "is_error_condition_enum", "thread", "tuple", "tuple_size", "tuple_element", "type_index", "is_void", "is_integral", "is_floating_point",
        "is_array", "is_enum", "is_union", "is_class", "is_function", "is_pointer", "is_lvalue_reference", "is_rvalue_reference", "is_member_object_pointer",
        "is_member_function_pointer", "is_fundamental", "is_arithmetic", "is_scalar", "is_object", "is_compound", "is_reference", "is_member_pointer",
        "is_const", "is_volatile", "is_trivial", "is_trivially_copyable", "is_standard_layout", "is_pod", "is_literal_type", "is_empty", "is_polymorphic",
        "is_abstract", "is_signed", "is_unsigned", "is_constructible", "is_trivially_constructible", "is_nothrow_constructible", "is_default_constructible",
        "is_trivially_default_constructible", "is_nothrow_default_constructible", "is_copy_constructible", "is_trivially_copy_constructible",
        "is_nothrow_copy_constructible", "is_move_constructible", "is_trivially_move_constructible", "is_nothrow_move_constructible",
        "is_assignable", "is_trivially_assignable", "is_nothrow_assignable", "is_copy_assignable", "is_trivially_copy_assignable",
        "is_nothrow_copy_assignable", "is_move_assignable", "is_trivially_move_assignable", "is_nothrow_move_assignable", "is_destructible",
        "is_trivially_destructible", "is_nothrow_destructible", "has_virtual_destructor", "alignment_of", "rank", "extent", "is_same",
        "is_base_of", "is_convertible", "remove_cv", "remove_const", "remove_volatile", "add_cv", "add_const", "add_volatile", "remove_reference",
        "add_lvalue_reference", "add_rvalue_reference", "remove_pointer", "add_pointer", "make_signed", "make_unsigned", "remove_extent",
        "remove_all_extents", "aligned_storage", "aligned_union", "decay", "enable_if", "conditional", "common_type", "underlying_type", "result_of",
        "integral_constant", "true_type", "false_type", "unordered_map", "unordered_set", "unordered_multimap", "unordered_multiset", "hasher",
        "key_equal", "piecewise_construct_t", "integer_sequence", "index_sequence", "make_integer_sequence", "make_index_sequence", "index_sequence_for",
        "shared_timed_mutex", "shared_lock", "tuple_element_t", "is_null_pointer", "remove_cv_t", "remove_const_t", "remove_volatile_t", "add_cv_t",
        "add_const_t", "add_volatile_t", "remove_reference_t", "add_lvalue_reference_t", "add_rvalue_reference_t", "remove_pointer_t", "add_pointer_t",
        "make_signed_t", "make_unsigned_t", "remove_extent_t", "remove_all_extents_t", "aligned_storage_t", "aligned_union_t", "decay_t", "enable_if_t",
        "conditional_t", "common_type_t", "underlying_type_t", "result_of_t", "any", "sequenced_policy", "parallel_policy", "parallel_unsequenced_policy",
        "is_execution_policy", "path", "directory_entry", "directory_iterator", "recursive_directory_iterator", "file_status", "space_info", "file_time_type",
        "default_order", "default_order_t", "default_searcher", "boyer_moore_searcher", "boyer_moore_horspool_searcher", "polymorphic_allocator",
        "memory_resource", "synchronized_pool_resource", "unsynchronized_pool_resource", "pool_options", "monotonic_buffer_resource", "scoped_lock",
        "optional", "nullopt_t", "basic_string_view", "string_view", "wstring_view", "u16string_view", "u32string_view", "shared_mutex",
        "bool_constant", "is_callable", "is_nowthrow_callable", "conjunction", "disjunction", "negation", "void_t", "has_unique_object_representations",
        "is_swappable", "is_swappable_with", "is_nothrow_swappable", "is_nothrow_swappable_with", "is_invocable", "is_invocable_r",
        "is_nothrow_invocable", "is_nothrow_invocable_r", "invoke_result", "invoke_result_t", "is_aggregate", "node_type", "insert_return_type",
        "in_place_tag", "in_place_t", "in_place_type_t", "in_place_index_t", "variant", "monostate", "variant_size", "variant_alternative",
        "variant_alternative_t", "endian", "weak_equality", "strong_equality", "partial_ordering", "weak_ordering", "strong_ordering",
        "common_comparison_category", "compare_three_way_result", "compare_three_way", "strong_order", "weak_order", "parital_order",
        "compare_strong_order_fallback", "compare_weak_order_fallback", "compare_parital_order_fallback", "formatter", "basic_format_parse_context",
        "format_parse_context", "wformat_parse_context", "basic_format_context", "format_context", "wformat_context", "basic_format_arg",
        "basic_format_args", "format_args", "wformat_args", "format_args_t", "format_error", "default_sentinel_t unreachable_sentinel_t",
        "source_location", "span", "basic_syncbuf", "basic_osyncstream", "syncbuf", "wsyncbuf", "osyncstream",
        "wosyncstream", "remove_cvref remove_cvref_t", "common_reference common_reference_t", "is_nothrow_convertible", "is_layout_compatible",
        "is_bounded_array", "is_unbounded_array", "is_pointer_interconvertible_base_of", "has_strong_structural_equality"}},
    {{"stlios"},{
        "boolalpha", "dec", "defaultfloat", "endl", "ends", "fixed", "floatfield", "flush", "get_money", "get_time",
        "hex", "hexfloat", "internal", "noboolalpha", "noshowbase", "noshowpoint", "noshowpos", "noskipws", "nounitbuf",
        "nouppercase", "oct", "put_money", "put_time", "resetiosflags", "scientific", "setbase", "setfill", "setiosflags", "setprecision",
        "setw", "showbase", "showpoint", "showpos", "skipws", "unitbuf", "uppercase", "ws" }},
    {{"stliterator"},{
        "const_iterator", "const_reverse_iterator", "front_insert_iterator", "insert_iterator", "istreambuf_iterator", "istream_iterator",
        "ostreambuf_iterator", "ostream_iterator", "iterator", "ostream_iterator", "output_iterator", "raw_storage_iterator", "move_iterator",
        "reverse_iterator", "bidirectional_iterator_tag", "forward_iterator_tag", "input_iterator_tag", "output_iterator_tag",
        "random_access_iterator_tag", "regex_iterator", "regex_token_iterator"}}
};
// clang-format on