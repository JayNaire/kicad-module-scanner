// This file was generated by qlalr - DO NOT EDIT!
#ifndef FOOTPRINT_GRAMMAR_P_H
#define FOOTPRINT_GRAMMAR_P_H

class footprint_grammar
{
public:
  enum VariousConstants {
    EOF_SYMBOL = 0,
    Token_AR = 36,
    Token_At = 31,
    Token_Cd = 25,
    Token_DA = 41,
    Token_DC = 42,
    Token_DS = 40,
    Token_Dr = 30,
    Token_I = 22,
    Token_Kw = 26,
    Token_Li = 24,
    Token_N = 20,
    Token_Na = 33,
    Token_Ne = 29,
    Token_Of = 34,
    Token_Op = 28,
    Token_Po = 23,
    Token_Ro = 35,
    Token_Sc = 27,
    Token_Sh = 32,
    Token_T = 39,
    Token_T0 = 37,
    Token_T1 = 38,
    Token_V = 21,
    Token_beginindex = 8,
    Token_beginmodule = 6,
    Token_beginpad = 10,
    Token_beginshape3d = 15,
    Token_endindex = 9,
    Token_endmodule = 7,
    Token_endpad = 12,
    Token_endshape3d = 16,
    Token_float = 2,
    Token_hex = 18,
    Token_identifier = 17,
    Token_index = 3,
    Token_keywords = 5,
    Token_moduleattributes = 19,
    Token_name = 4,
    Token_number = 1,
    Token_padattribute = 14,
    Token_padshape = 13,
    Token_quotedstring = 11,

    ACCEPT_STATE = 189,
    RULE_COUNT = 109,
    STATE_COUNT = 191,
    TERMINAL_COUNT = 43,
    NON_TERMINAL_COUNT = 72,

    GOTO_INDEX_OFFSET = 191,
    GOTO_INFO_OFFSET = 188,
    GOTO_CHECK_OFFSET = 188
  };

  static const char  *const    spell [];
  static const short             lhs [];
  static const short             rhs [];

#ifndef QLALR_NO_FOOTPRINT_GRAMMAR_DEBUG_INFO
  static const int     rule_index [];
  static const int      rule_info [];
#endif // QLALR_NO_FOOTPRINT_GRAMMAR_DEBUG_INFO

  static const short    goto_default [];
  static const short  action_default [];
  static const short    action_index [];
  static const short     action_info [];
  static const short    action_check [];

  static inline int nt_action (int state, int nt)
  {
    const int yyn = action_index [GOTO_INDEX_OFFSET + state] + nt;
    if (yyn < 0 || action_check [GOTO_CHECK_OFFSET + yyn] != nt)
      return goto_default [nt];

    return action_info [GOTO_INFO_OFFSET + yyn];
  }

  static inline int t_action (int state, int token)
  {
    const int yyn = action_index [state] + token;

    if (yyn < 0 || action_check [yyn] != token)
      return - action_default [state];

    return action_info [yyn];
  }
};


#endif // FOOTPRINT_GRAMMAR_P_H

