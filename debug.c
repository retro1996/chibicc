#include "chibicc.h"
#define DEBUG_C "debug.c"

//  for debug needs
char *tokenkind2str(TokenKind kind)
{
    switch (kind)
    {
    case TK_IDENT:
        return "TK_IDENT";
    case TK_PUNCT:
        return "TK_PUNCT";
    case TK_KEYWORD:
        return "TK_KEYWORD";
    case TK_STR:
        return "TK_STR";
    case TK_NUM:
        return "TK_NUM";
    case TK_PP_NUM:
        return "TK_PP_NUM";
    case TK_EOF:
        return "TK_EOF";
    default:
        return "UNREACHABLE";
    }
}

// print all tokens received
void print_debug_tokens(char *currentfilename, char *function, Token *tok)
{

    fprintf(f, "=====================file : %s, function: %s\n", currentfilename, function);

    // for debug needs print all the tokens with values
    Token *t = tok;
    while (t->kind != TK_EOF)
    {
        if (t->len > 0)
        {
            char tokloc[t->len + 1];
            memset(tokloc, 0, sizeof(tokloc));
            char *ptokloc = &tokloc[0];
            strncpy(ptokloc, t->loc, t->len);
            fprintf(f, "token->kind: %s, token->len: %d, token->val: %ld, token->fval:%Lf \n", tokenkind2str(t->kind), t->len, t->val, t->fval);
            fprintf(f, "     token->str: %s, token->filename: %s, token->line_no: %d, token->at_bol:%d \n", t->str, t->filename, t->line_no, t->at_bol);
            fprintf(f, "     token->loc: %s \n", ptokloc);
        }
        // TK_EOF not sure that it helps to have this information in the log!
        //  else
        //  {
        //    fprintf(f, "token->kind: %s, token->len: %d, token->val: %ld, token->fval:%Lf \n", tokenkind2str(t->kind), t->len, t->val, t->fval);
        //    fprintf(f, "     token->str: %s, token->filename: %s, token->line_no: %d, token->at_bol:%d \n", t->str, t->filename, t->line_no, t->at_bol);
        //  }
        t = t->next;
    }
}


void emit_debug_info(Obj *prog) {
  if (!opt_g)
    return;

  static int c = 0;
  static int label_count = 0;

  println("  .section .debug_abbrev,\"\",@progbits");
  println(".L.debug_abbrev%d:", c);

  println("  .uleb128 1");                    // Abbrev code
  println("  .uleb128 0x11");                 // DW_TAG_compile_unit
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x25");                 // DW_AT_producer
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x13");                 // DW_AT_language
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x10");                 // DW_AT_stmt_list
  println("  .uleb128 0x17");                 // DW_FORM_sec_offset
  println("  .uleb128 0x11");                 // DW_AT_low_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x12");                 // DW_AT_high_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 2");                    // Abbrev code
  println("  .uleb128 0x2e");                 // DW_TAG_subprogram
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x3a");                 // DW_AT_decl_file
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x3b");                 // DW_AT_decl_line
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x11");                 // DW_AT_low_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x12");                 // DW_AT_high_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x40");                 // DW_AT_frame_base
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .uleb128 0x3f");                 // DW_AT_external
  println("  .uleb128 0xc");                  // DW_FORM_flag
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 3");                    // Abbrev code
  println("  .uleb128 0x5");                  // DW_TAG_formal_parameter
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x2");                  // DW_AT_location
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 4");                    // Abbrev code
  println("  .uleb128 0x34");                 // DW_TAG_variable
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x2");                  // DW_AT_location
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 5");                    // Abbrev code
  println("  .uleb128 0x24");                 // DW_TAG_base_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x3e");                 // DW_AT_encoding
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .uleb128 0xb");                  // DW_AT_byte_size
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .byte 0");
  println("  .byte 0");

  println("  .byte 0");                       // End of abbrevs

  println("  .section .debug_info,\"\",@progbits");
  println(".L.debug_info%d:", c);
  println("  .long .L.debug_info_end%d - .L.debug_info_start%d", c, c);
  println(".L.debug_info_start%d:", c);
  println("  .short 4");
  println("  .long .L.debug_abbrev%d", c);
  println("  .byte 8");

  println("  .uleb128 1");
  println("  .string \"chibicc\"");
  println("  .byte 0xc");                     // DW_LANG_C99
  println("  .string \"%s\"", base_file);
  println("  .long 0");
  println("  .quad .L.text_start");
  println("  .quad .L.text_end");

  // Emit base types
  println(".L.type_int%d:", c);
  println("  .uleb128 5");
  println("  .string \"int\"");
  println("  .byte 5"); // DW_ATE_signed
  println("  .byte 4");

  println(".L.type_char%d:", c);
  println("  .uleb128 5");
  println("  .string \"char\"");
  println("  .byte 6"); // DW_ATE_signed_char
  println("  .byte 1");

  println(".L.type_long%d:", c);
  println("  .uleb128 5");
  println("  .string \"long\"");
  println("  .byte 5"); // DW_ATE_signed
  println("  .byte 8");

  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    
    if (!fn->is_live)
      continue;

    println("  .uleb128 2");
    println("  .string \"%s\"", fn->name);
    println("  .uleb128 %d", fn->file_no);
    println("  .uleb128 %d", fn->line_no);
    println("  .quad %s", fn->name);
    println("  .quad .L.end.%s", fn->name);
    
    // Frame base: DW_OP_reg6 (rbp)
    println("  .byte 1");
    println("  .byte 0x56");
    
    println("  .byte %d", !fn->is_static);

    for (Obj *var = fn->params; var; var = var->next) {
        if (!var->name) continue;
        println("  .uleb128 3");
        println("  .string \"%s\"", var->name);
        
        if (var->ty->kind == TY_INT)
            println("  .long .L.type_int%d - .L.debug_info%d", c, c);
        else if (var->ty->kind == TY_CHAR)
            println("  .long .L.type_char%d - .L.debug_info%d", c, c);
        else if (var->ty->kind == TY_LONG)
            println("  .long .L.type_long%d - .L.debug_info%d", c, c);
        else
            println("  .long .L.type_int%d - .L.debug_info%d", c, c);

        int lbl = label_count++;
        println("  .uleb128 .L.loc_end_%d - .L.loc_start_%d", lbl, lbl);
        println(".L.loc_start_%d:", lbl);
        println("  .byte 0x91"); // DW_OP_fbreg
        println("  .sleb128 %d", var->offset);
        println(".L.loc_end_%d:", lbl);
    }

    for (Obj *var = fn->locals; var; var = var->next) {
        if (var->is_param || !var->name) continue;
        println("  .uleb128 4");
        println("  .string \"%s\"", var->name);
        
        if (var->ty->kind == TY_INT)
            println("  .long .L.type_int%d - .L.debug_info%d", c, c);
        else if (var->ty->kind == TY_CHAR)
            println("  .long .L.type_char%d - .L.debug_info%d", c, c);
        else if (var->ty->kind == TY_LONG)
            println("  .long .L.type_long%d - .L.debug_info%d", c, c);
        else
            println("  .long .L.type_int%d - .L.debug_info%d", c, c);

        int lbl = label_count++;
        println("  .uleb128 .L.loc_end_%d - .L.loc_start_%d", lbl, lbl);
        println(".L.loc_start_%d:", lbl);
        println("  .byte 0x91"); // DW_OP_fbreg
        println("  .sleb128 %d", var->offset);
        println(".L.loc_end_%d:", lbl);
    }

    println("  .byte 0"); // End of children
  }

  println("  .byte 0");
  println(".L.debug_info_end%d:", c);
}
