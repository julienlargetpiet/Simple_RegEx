#include "layer0.h"

std::map<std::vector<unsigned int>, std::map<bool, std::string>> regex_findr(std::string &searched, std::string &x) {
  char cur_chr;
  unsigned int i = 0;
  unsigned int cnt = 0;
  unsigned int pre_cnt2;
  unsigned int ref_cnt;
  unsigned int ref_i;
  const unsigned int n = searched.length();
  const unsigned int n2 = x.length();
  bool agn;
  bool agn2;
  bool or_state = 0;
  unsigned int ref_int1;
  unsigned int ref_int2;
  bool range_state;
  bool cur_found;
  unsigned int rep_val;
  unsigned int rep_val_cnt;
  unsigned int ref_rep_val = 1;
  unsigned int jump_i;
  unsigned int jump_i2;
  unsigned int jump_i3;
  unsigned int idx_cnt = 0;
  unsigned int cur_lmt;
  unsigned int ref_cur_lmt;
  unsigned int bf_rep_val;
  bool greedy_state1 = 0;
  bool greedy_state2 = 0;
  std::vector<unsigned int> multiple_cnt = {};
  std::vector<unsigned int> ref_multiple_cnt = {};
  std::string cur_matched_str = "";
  std::vector<std::string> matched_str;
  std::vector<std::string> pre_matched_str;
  std::string rtn_str;
  unsigned int lst_cnt;
  unsigned int pre_cnt;
  unsigned int cur_ref_cnt;
  unsigned int cur_ref_i;
  unsigned int temp_i;
  bool is_repetition = 0;
  std::vector<unsigned int> sorted_v;
  unsigned int cur_idx;
  unsigned int bf_cnt_zero = 0;
  while (cnt < n2) {
    greedy_state2 = 0;
    if (searched[i] == '\\') {
      i += 1;
    } else {
      if (searched[i] == '[') {
        or_state = 1;
        i += 1;
        jump_i = i;
        while (searched[jump_i] != ']' & searched[jump_i - 1] != '\\') {
          jump_i += 1;
        };
        jump_i2 = jump_i;
        if (jump_i + 2 < n) {
          if (searched[jump_i + 1] == '{') {
            is_repetition = 1;
            rep_val = 1;
            jump_i += 2;
            if (jump_i + 1 < n) {
              if (searched[jump_i] == '+') {
                greedy_state1 = 1;
                jump_i += 1;
              };
              if (searched[jump_i] != '}') {
                ref_rep_val = (int(searched[jump_i]) - 48);
                jump_i += 1;
                while (searched[jump_i] != '}') {
                  ref_rep_val *= 10;
                  ref_rep_val += (int(searched[jump_i]) - 48);
                  jump_i += 1;
                };
              } else {
                return {{{0, 0}, {{0, ""}}}};
              };
            } else {
              return {{{0, 0}, {{0, ""}}}};
            };
          };
        };
      };
    };
    rep_val = 1;
    cur_ref_i = i;
    cur_found = 0;
    range_state = 0;
    ref_int1 = int(searched[i]);
    if (i + 1 < n) {
      if (searched[i + 1] == '-') {
        i += 2;
        if (!(i < n)) {
          return {{{0, 0}, {{0, ""}}}};
        };
        range_state = 1;
        ref_int2 = int(searched[i]);
        while (!cur_found & cnt < n2) {
          cur_found = (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2);
          cnt += 1;
        };
      } else {
        while (!cur_found & cnt < n2) {
          cur_found = (ref_int1 == int(x[cnt])); 
          cnt += 1;
        };
      };
    } else {
      while (!cur_found & cnt < n2) {
        cur_found = (ref_int1 == int(x[cnt])); 
        cnt += 1;
      };
    };
    cur_matched_str = x[cnt - 1];
    i += 1;
    if (cur_found & i < n) {
      if (searched[i] != '\\') {
        if (searched[i] == '{') {
          is_repetition = 1;
          i += 1;
          if (searched[i] == '+') {
            greedy_state2 = 1;
            i += 1;
          };
          if (searched[i] != '}') {
            rep_val = int(searched[i]) - 48;
            i += 1;
            while (searched[i] != '}') {
              rep_val *= 10;
              rep_val += (int(searched[i]) - 48);
              i += 1;
            };
          } else {
            return {{{0, 0}, {{0, ""}}}};
          };
          i += 1;
        };
      } else {
        i += 1;
      };
      if (greedy_state2 & rep_val == 0) {
        rep_val = 1;
      };
      if (range_state & is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        bf_rep_val = rep_val;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val + ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            cur_ref_cnt = cnt;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
          cnt = cur_ref_cnt;
        };
        rep_val = 1;
      } else if (is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        bf_rep_val = rep_val;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) == ref_int1;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val + ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            cur_ref_cnt = cnt;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) == ref_int1;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
          cnt = cur_ref_cnt;
        };
        rep_val = 1;
      };
      pre_cnt2 = cnt;
    } else {
      if (ref_rep_val == 0) {
        if (cur_found) {
          cur_found = 0;
        } else {
          cur_found = 1;
          pre_cnt2 = cnt;
          cur_matched_str = ""; 
        };
        if (i + 3 < n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
            i += 4;
          };
        } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          };
        };
      } else if (i + 3 < n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            cur_matched_str = ""; 
            pre_cnt2 = cnt;
          };
          i += 3;
        } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            pre_cnt2 = cnt;
            cur_matched_str = ""; 
          };
          i += 4;
        };
      } else if (i + 3 == n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            pre_cnt2 = cnt;
            cur_matched_str = ""; 
          };
          i += 3;
        };
      };
    };
    if (cnt < n2 & cur_found) {
      if (range_state) {
        agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
        if (agn2) {
          for (temp_i = 0; temp_i + 1 < cur_matched_str.length(); ++temp_i) {
            cur_matched_str[temp_i] = cur_matched_str[temp_i + 1];   
          };
          cur_matched_str[cur_matched_str.length() - 1] = x[cnt];
          cnt += 1;
          while (agn2 & cnt < n2) {
            agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
            if (agn2) {
              for (temp_i = 0; temp_i + 1 < cur_matched_str.length(); ++temp_i) {
                cur_matched_str[temp_i] = cur_matched_str[temp_i + 1];   
              };
              cur_matched_str[cur_matched_str.length() - 1] = x[cnt];
              cnt += 1;
            };
          };
        };
      } else {
        agn2 = int(x[cnt]) == ref_int1;
        if (agn2) {
          cnt += 1;
          while (agn2 & cnt < n2) {
            agn2 = int(x[cnt]) == ref_int1;
            if (agn2) {
              cnt += 1;
            };
          };
        };
      };
    };
    if (rep_val == 0 || ref_rep_val == 0) {
      if (bf_cnt_zero + 1 < pre_cnt2) {
        cur_found = 1;
        ref_i = i;
        while (bf_cnt_zero + 1 < pre_cnt2) {
          matched_str.push_back("");
          multiple_cnt.push_back(bf_cnt_zero);
          bf_cnt_zero += 1;
        };
        if (pre_cnt2 == n2 & x[n2 - 1] != ref_int1) {
          matched_str.push_back("");
          multiple_cnt.push_back(bf_cnt_zero);
        };
        if (or_state) {
          ref_i = jump_i + 1;
        };
      };
      bf_cnt_zero = cnt;
    };
    if (or_state) {
      rep_val = 1;
      if (cur_found & rep_val != 0 & ref_rep_val != 0) {
        multiple_cnt.push_back(cnt);
        matched_str.push_back(cur_matched_str);
        ref_i = jump_i + 1;
      };
      if (cnt == n2) {
        if (i < jump_i2) {
          cnt = 0;
          bf_cnt_zero = 0;
        } else {
          or_state = 0;
          greedy_state1 = 0;
          break;
        };
      } else {
        i = cur_ref_i; 
      };
    } else if (cur_found & rep_val != 0 & ref_rep_val != 0) {
      multiple_cnt.push_back(cnt);
      matched_str.push_back(cur_matched_str);
      ref_i = i;
      is_repetition = 0;
      rep_val = 1;
      i = 0;
    } else {
      i = 0;
    };
  };
  cur_matched_str = "";
  const unsigned int n_cnt = multiple_cnt.size();
  if (n_cnt == 0) {
    return {{{0, 0}, {{0, ""}}}};
  };
  i = ref_i;
  sorted_v = sort_ascout(multiple_cnt);
  for (temp_i = 0; temp_i < n_cnt; ++temp_i) {
    cur_idx = match(multiple_cnt, sorted_v[temp_i]);
    pre_matched_str.push_back(matched_str[cur_idx]);
  };
  multiple_cnt = sorted_v;
  cnt = multiple_cnt[0];
  if (cnt == n2) {
    temp_i = ref_i;
    while (temp_i < n) {
      if (searched[temp_i] != '\\') {
        temp_i += 1;
        if (searched[temp_i] == '{') {
          temp_i += 1;
          if (searched[temp_i] != '0') {
            return {{{{0, 0}}, {{0, ""}}}};
          };
        } else if (searched[temp_i] == '^') {
          temp_i += 1;
          if (temp_i + 2 < n) {
            if (searched[temp_i + 1] == '-') {
              temp_i += 2;
              if (searched[temp_i] != '~' & searched[temp_i - 2] != ' ') {
                return {{{{0, 0}}, {{0, ""}}}};
              } else if (searched[temp_i] != ' ' & searched[temp_i - 2] != '~') {
                return {{{{0, 0}}, {{0, ""}}}};
              };
            } else {
              return {{{{0, 0}}, {{0, ""}}}};
            };
          } else {
            return {{{{0, 0}}, {{0, ""}}}};
          };
        } else {
          return {{{{0, 0}}, {{0, ""}}}};
        };
      };
      temp_i += 1;
    };
    pre_cnt = cnt - matched_str[0].length();
    lst_cnt = cnt - 1;
    return {{{{pre_cnt, lst_cnt}}, {{1, matched_str[0]}}}};
  };
  if (pre_matched_str[0] != "") {
    lst_cnt = multiple_cnt[0] - 1;
  } else {
    lst_cnt = multiple_cnt[0];
  };
  matched_str = pre_matched_str;
  ref_rep_val = 1;
  is_repetition = 0;
  greedy_state1 = 0;
  while (i < n & cnt < n2) {
    greedy_state2 = 0;
    if (searched[i] == '\\') {
      i += 1;
    } else {
      if (searched[i] == '[') {
        ref_cnt = cnt;
        or_state = 1;
        i += 1;
        jump_i = i;
        while (searched[jump_i] != ']' & searched[jump_i - 1] != '\\') {
          jump_i += 1;
        };
        jump_i2 = jump_i;
        if (jump_i + 2 < n) {
          if (searched[jump_i + 1] == '{') {
            is_repetition = 1;
            rep_val = 1;
            jump_i += 2;
            if (jump_i + 1 < n) {
              if (searched[jump_i] == '+') {
                  greedy_state1 = 1;
                  jump_i += 1;
              };
            } else {
              return {{{0, 0}, {{0, ""}}}};
            };
            if (searched[jump_i] != '}') {
              ref_rep_val = (int(searched[jump_i]) - 48);
              jump_i += 1;
              while (searched[jump_i] != '}') {
                ref_rep_val *= 10;
                ref_rep_val += (int(searched[jump_i]) - 48);
                jump_i += 1;
              };
            } else {
              return {{{0, 0}, {{0, ""}}}};
            };
          };
        };
      };
    };
    rep_val = 1;
    cur_found = 0;
    range_state = 0;
    ref_int1 = int(searched[i]);
    if (i + 1 < n) {
      if (searched[i + 1] == '-') {
        i += 2;
        if (!(i < n)) {
          return {{{0, 0}, {{0, ""}}}};
        };
        range_state = 1;
        ref_int2 = int(searched[i]);
        if (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2) {
          cur_found = 1;
        };
      } else if (ref_int1 == int(x[cnt])) {
        cur_found = 1;
      };
    } else if (ref_int1 == int(x[cnt])) {
      cur_found = 1;
    };
    cur_matched_str = x[cnt];
    i += 1;
    cnt += 1;
    if (cur_found & i < n) {
      if (searched[i] != '\\') {
        if (searched[i] == '{') {
          is_repetition = 1;
          i += 1;
          if (searched[i] == '+') {
            greedy_state2 = 1;
            i += 1;
          };
          if (searched[i] != '}') {
            rep_val = int(searched[i]) - 48;
            i += 1;
            while (searched[i] != '}') {
              rep_val *= 10;
              rep_val += (int(searched[i]) - 48);
              i += 1;
            };
          } else {
            return {{{0, 0}, {{0, ""}}}};
          };
          i += 1;
        };
      } else {
        i += 1;
      };
      if (greedy_state2 & rep_val == 0) {
        rep_val = 1;
      };
      bf_rep_val = rep_val;
      if (range_state & is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
        };
        rep_val = 1;
      } else if (is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) == ref_int1;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) == ref_int1;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
        };
        rep_val = 1;
      };
      if (rep_val == 0 || ref_rep_val == 0) {
        cur_found = 0;
        cur_matched_str = "";
      };
    } else {
      if (ref_rep_val == 0) {
        if (cur_found) {
          cur_found = 0;
        } else {
          cur_found = 1;
          cur_matched_str = "";
        };
        if (i + 3 < n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
            i += 4;
          };
        } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          };
        };
      } else if (i + 3 < n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          i += 3;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            cur_matched_str = "";
          };
        } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
          i += 4;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            cur_matched_str = "";
          };
        };
      } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          i += 3;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
            cur_matched_str = "";
          };
        };
      };
    };
    if (rep_val == 0 || ref_rep_val == 0) {
      cnt -= 1;
    };
    if (or_state) {
      rep_val = 1;
      if (cur_found) {
        matched_str[idx_cnt] += cur_matched_str;
        i = jump_i + 1;
        lst_cnt = cnt - 1;
        or_state = 0;
        greedy_state1 = 0;
        is_repetition = 0;
        ref_rep_val = 1;
      } else {
        if (i == jump_i2) {
          if (idx_cnt + 1 < n_cnt) {
            idx_cnt += 1;
            cnt = multiple_cnt[idx_cnt];
            i = ref_i;
            or_state = 0;
            greedy_state1 = 0;
            ref_rep_val = 1;
            is_repetition = 0;
          } else {
            return {{{0, 0}, {{0, ""}}}};
          };
        } else {
          cnt = ref_cnt;
        };
      };
    } else if (!cur_found) {
      if (idx_cnt + 1 < n_cnt) {
        idx_cnt += 1;
        is_repetition = 0;
        greedy_state1 = 0;
        ref_rep_val = 1;
        cnt = multiple_cnt[idx_cnt];
        i = ref_i;
      } else {
        return {{{0, 0}, {{0, ""}}}};
      };
    } else {
      matched_str[idx_cnt] += cur_matched_str;
      lst_cnt = cnt - 1;
      is_repetition = 0;
      rep_val = 1;
    };
  };
  rtn_str = matched_str[idx_cnt];
  pre_cnt = multiple_cnt[idx_cnt] - pre_matched_str[idx_cnt].length();
  return {{{pre_cnt, lst_cnt}, 
          {{cur_found, rtn_str}}}}; 
};

//@T regex_findr_bgn
//@U std::map&lt;std::vector&lt;std::vector&lt;unsigned int&gt;&gt;, std::vector&lt;std::string&gt;&gt; regex_findr_bgn(std::string &searched, std::string &x)
//@X
//@D Returns where the string matches the first condition of the search string. Used by more abstract functions.
//@A searched : is the search string
//@A x : is the string to search in for patterns
//@X
//@E
//@X

std::map<std::vector<std::vector<unsigned int>>, std::vector<std::string>> regex_findr_bgn(std::string searched, std::string x) {
  std::map<std::vector<unsigned int>, std::map<bool, std::string>> cur_mp;
  std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator cur_it;
  std::map<bool, std::string>::iterator rslt_mp;
  std::vector<unsigned int> idx_v;
  std::vector<unsigned int> conditions_idx_v = {1};
  std::vector<std::string> hmn_str_idxv = {};
  std::vector<unsigned int> cur_hmn_idxv = {};
  std::vector<std::vector<unsigned int>> hmn_idxv = {};
  unsigned int ncx = searched.length();
  unsigned int temp_cnt;
  unsigned int temp_cnt2;
  unsigned int cur_lmt;
  unsigned int rtn_pre_cnt;
  unsigned int rtn_lst_cnt = 0;
  unsigned int ref_mult;
  unsigned int ref_mult2;
  unsigned int ref_temp_cnt2;
  unsigned int cur_par = 0;
  bool bgn_par = 0;
  bool greedy_state;
  bool par_content;
  bool is_found;
  std::string cur_str;
  std::string cur_x;
  std::string ref_cur_x;
  std::string break_ptrn = "";
  std::string cur_break_ptrn;
  std::string cur_searched;
  if (searched[0] == '[') {
    temp_cnt = 2;
    while (searched[temp_cnt] != ']' & searched[temp_cnt - 1] != '\\') {
      if (searched[temp_cnt] == '{' & searched[temp_cnt - 1] != '\\') {
        bgn_par = 1;
      } else if (searched[temp_cnt] == '}' & searched[temp_cnt - 1] != '\\') {
        bgn_par = 0;
      } else if (!bgn_par) {
        conditions_idx_v.push_back(temp_cnt);
      };
      temp_cnt += 1;
    };
    conditions_idx_v.push_back(temp_cnt);
    if (temp_cnt + 4 < ncx) {
      temp_cnt += 1;
      if (searched[temp_cnt] == '{' & searched[temp_cnt + 1] == '?') {
        cur_x = x;
        temp_cnt += 2;
        cur_par = 1;
        while (1) {
          if (searched[temp_cnt] == '}' & searched[temp_cnt - 1] != '\\') {
            cur_par -= 1;
            if (cur_par == 0) {
              break;
            };
          } else if (searched[temp_cnt] == '{' & searched[temp_cnt - 1] != '\\') {
            cur_par += 1;
          };
          break_ptrn.push_back(searched[temp_cnt]);
          temp_cnt += 1;
          if (temp_cnt == ncx) {
            break;
          };
        };
        cur_mp = regex_findr(break_ptrn, x);
        cur_it = cur_mp.begin();
        rslt_mp = cur_it->second.begin();
        if (rslt_mp->first) {
          idx_v = cur_it->first;
          rtn_pre_cnt = idx_v[0];
          cur_x = "";
          for (temp_cnt = 0; temp_cnt < rtn_pre_cnt; ++temp_cnt) {
            cur_x.push_back(x[temp_cnt]);
          };
        };
        ref_cur_x = cur_x;
        for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
          cur_x = ref_cur_x;
          rtn_lst_cnt = 0;
          par_content = 0;
          cur_searched = "";
          temp_cnt2 = conditions_idx_v[temp_cnt];
          cur_lmt = conditions_idx_v[temp_cnt + 1];
          while (temp_cnt2 < cur_lmt) {
            if (searched[temp_cnt2] == '{' & searched[temp_cnt2] != '\\') {
              par_content = 1;
              break;
            };
            cur_searched.push_back(searched[temp_cnt2]);
            temp_cnt2 += 1;
          };
          cur_break_ptrn = "";
          if (par_content) {
            temp_cnt2 += 1;
            cur_par = 1;
            if (searched[temp_cnt2] == '?') {
              temp_cnt2 += 1;
              while (1) {
                if (searched[temp_cnt2] == '}' & searched[temp_cnt2 - 1] != '\\') {
                  cur_par -= 1;
                  if (cur_par == 0) {
                    break;
                  };
                } else if (searched[temp_cnt2] == '{' & searched[temp_cnt2 - 1] != '\\') {
                  cur_par += 1;
                };
                cur_break_ptrn.push_back(searched[temp_cnt2]);
                temp_cnt2 += 1;
              };
              cur_mp = regex_findr(cur_break_ptrn, cur_x);
              cur_it = cur_mp.begin();
              rslt_mp = cur_it->second.begin();
              if (rslt_mp->first) {
                idx_v = cur_it->first;
                rtn_pre_cnt = idx_v[0];
                cur_x = "";
                for (temp_cnt2 = 0; temp_cnt2 < rtn_pre_cnt; ++temp_cnt2) {
                  cur_x.push_back(x[temp_cnt2]);
                };
              };
            } else {
              cur_searched.push_back('{');
              while (1) {
                if (searched[temp_cnt2] == '}' & searched[temp_cnt2] != '\\') {
                  cur_par -= 1;
                  if (cur_par == 0) {
                    break;
                  };
                } else if (searched[temp_cnt2] == '{' & searched[temp_cnt2] != '\\') {
                  cur_par += 1;
                };
                cur_searched.push_back(searched[temp_cnt2]);
                temp_cnt2 += 1;
              };
              cur_searched.push_back('}');
            };
          };
          cur_hmn_idxv = {};
          ncx = cur_x.length();
          is_found = 0;
          while (1) {
            cur_mp = regex_findr1sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              is_found = 1;
              cur_str = rslt_mp->second;
              idx_v = cur_it->first;
              rtn_lst_cnt += idx_v[1];
              cur_hmn_idxv.push_back(rtn_lst_cnt);
            } else {
              break;
            };
            if (rtn_lst_cnt + 1 < ncx) {
              cur_x = "";
              for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
                cur_x.push_back(x[temp_cnt2]);
              };
              rtn_lst_cnt += 1;
            } else {
              break;
            };
          };
          if (is_found) {
            hmn_idxv.push_back(cur_hmn_idxv);
            hmn_str_idxv.push_back(cur_str);
          };
        };
      } else if (searched[temp_cnt] == '{') {
        ncx = x.length();
        temp_cnt += 1;
        if (searched[temp_cnt] == '+')  {
          temp_cnt += 1;
        };
        ref_mult = int(searched[temp_cnt]) - 48;
        temp_cnt += 1;
        while (searched[temp_cnt] != '}') {
          temp_cnt *= 10;
          ref_mult += (int(searched[temp_cnt]) - 48);
          temp_cnt += 1;
        };
        for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
          rtn_lst_cnt = 0;
          par_content = 0;
          cur_lmt = conditions_idx_v[temp_cnt + 1];
          cur_searched = "";
          temp_cnt2 = conditions_idx_v[temp_cnt];
          while (temp_cnt2 < cur_lmt) {
            cur_searched.push_back(searched[temp_cnt2]);
            temp_cnt2 += 1;
          };
          cur_searched.insert(0, 1, '[');
          cur_searched.push_back(']');
          cur_searched.push_back('{');
          cur_searched += std::to_string(ref_mult);
          cur_searched.push_back('}');
          cur_x = x;
          cur_hmn_idxv = {};
          is_found = 0;
          while (1) {
            cur_mp = regex_findr1sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              is_found = 1;
              idx_v = cur_it->first;
              rtn_lst_cnt += idx_v[1];
              cur_str = rslt_mp->second;
              cur_hmn_idxv.push_back(rtn_lst_cnt);
            } else {
              break;
            };
            if (rtn_lst_cnt + 1 < ncx) {
              cur_x = "";
              for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
                cur_x.push_back(x[temp_cnt2]);
              };
              rtn_lst_cnt += 1;
            } else {
              break;
            };
          };
          if (is_found) {
            hmn_idxv.push_back(cur_hmn_idxv);
            hmn_str_idxv.push_back(cur_str);
          };
        };
      } else {
        ncx = x.length();
        for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
          rtn_lst_cnt = 0;
          cur_searched = "";
          cur_lmt = conditions_idx_v[temp_cnt + 1];
          for (temp_cnt2 = conditions_idx_v[temp_cnt]; temp_cnt2 < cur_lmt; ++temp_cnt2) {
            cur_searched.push_back(searched[temp_cnt2]);
          };
          cur_x = x;
          cur_hmn_idxv = {};
          is_found = 0;
          while (1) {
            cur_mp = regex_findr1sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              is_found = 1;
              idx_v = cur_it->first;
              rtn_lst_cnt += idx_v[1];
              cur_hmn_idxv.push_back(rtn_lst_cnt);
              cur_str = rslt_mp->second;
            } else {
              break;
            };
            if (rtn_lst_cnt + 1 < ncx) {
              cur_x = "";
              for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
                cur_x.push_back(x[temp_cnt2]);
              };
              rtn_lst_cnt += 1;
            } else {
              break;
            };
          };
          if (is_found) {
            hmn_idxv.push_back(cur_hmn_idxv);
            hmn_str_idxv.push_back(cur_str);
          };
        };
      };
    } else if (temp_cnt + 1 < ncx) { 
      if (searched[temp_cnt + 1] == '{') {
        ncx = x.length();
        temp_cnt += 2;
        ref_mult = int(searched[temp_cnt]) - 48;
        temp_cnt += 1;
        while (searched[temp_cnt] != '}') {
          temp_cnt *= 10;
          ref_mult += (int(searched[temp_cnt]) - 48);
          temp_cnt += 1;
        };
        for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
          rtn_lst_cnt = 0;
          par_content = 0;
          cur_lmt = conditions_idx_v[temp_cnt + 1];
          cur_searched = "";
          temp_cnt2 = conditions_idx_v[temp_cnt];
          while (temp_cnt2 < cur_lmt) {
            cur_searched.push_back(searched[temp_cnt2]);
            temp_cnt2 += 1;
          };
          cur_searched.insert(0, 1, '[');
          cur_searched.push_back(']');
          cur_searched.push_back('{');
          cur_searched += std::to_string(ref_mult);
          cur_searched.push_back('}');
          cur_x = x;
          cur_hmn_idxv = {};
          is_found = 0;
          while (1) {
            cur_mp = regex_findr1sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              is_found = 1;
              idx_v = cur_it->first;
              rtn_lst_cnt += idx_v[1];
              cur_str = rslt_mp->second;
              cur_hmn_idxv.push_back(rtn_lst_cnt);
            } else {
              break;
            };
            if (rtn_lst_cnt + 1 < ncx) {
              cur_x = "";
              for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
                cur_x.push_back(x[temp_cnt2]);
              };
              rtn_lst_cnt += 1;
            } else {
              break;
            };
          };
          if (is_found) {
            hmn_idxv.push_back(cur_hmn_idxv);
            hmn_str_idxv.push_back(cur_str);
          };
        };
      } else {
        ncx = x.length();
        for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
          rtn_lst_cnt = 0;
          cur_searched = "";
          cur_lmt = conditions_idx_v[temp_cnt + 1];
          for (temp_cnt2 = conditions_idx_v[temp_cnt]; temp_cnt2 < cur_lmt; ++temp_cnt2) {
            cur_searched.push_back(searched[temp_cnt2]);
          };
          cur_x = x;
          cur_hmn_idxv = {};
          is_found = 0;
          while (1) {
            cur_mp = regex_findr1sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              is_found = 1;
              idx_v = cur_it->first;
              rtn_lst_cnt += idx_v[1];
              cur_hmn_idxv.push_back(rtn_lst_cnt);
              cur_str = rslt_mp->second;
            } else {
              break;
            };
            if (rtn_lst_cnt + 1 < ncx) {
              cur_x = "";
              for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
                cur_x.push_back(x[temp_cnt2]);
              };
              rtn_lst_cnt += 1;
            } else {
              break;
            };
          };
          if (is_found) {
            hmn_idxv.push_back(cur_hmn_idxv);
            hmn_str_idxv.push_back(cur_str);
          };
        };
      };
    } else {
      ncx = x.length();
      for (temp_cnt = 0; temp_cnt + 1 < conditions_idx_v.size(); ++temp_cnt) {
        rtn_lst_cnt = 0;
        cur_searched = "";
        cur_lmt = conditions_idx_v[temp_cnt + 1];
        for (temp_cnt2 = conditions_idx_v[temp_cnt]; temp_cnt2 < cur_lmt; ++temp_cnt2) {
          cur_searched.push_back(searched[temp_cnt2]);
        };
        cur_x = x;
        cur_hmn_idxv = {};
        is_found = 0;
        while (1) {
          cur_mp = regex_findr1sub(cur_searched, cur_x);
          cur_it = cur_mp.begin();
          rslt_mp = cur_it->second.begin();
          if (rslt_mp->first) {
            is_found = 1;
            idx_v = cur_it->first;
            rtn_lst_cnt += idx_v[1];
            cur_hmn_idxv.push_back(rtn_lst_cnt);
            cur_str = rslt_mp->second;
          } else {
            break;
          };
          if (rtn_lst_cnt + 1 < ncx) {
            cur_x = "";
            for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
              cur_x.push_back(x[temp_cnt2]);
            };
            rtn_lst_cnt += 1;
          } else {
            break;
          };
        };
        if (is_found) {
          hmn_idxv.push_back(cur_hmn_idxv);
          hmn_str_idxv.push_back(cur_str);
        };
      };
    };
  } else {
    cur_x = x;
    cur_searched = searched[0];
    if (ncx > 1) {
      temp_cnt2 = 1;
      if (searched[temp_cnt2] == '{') {
        if (searched[temp_cnt2 + 1] != '?') {
          while (1) {
            cur_searched.push_back(searched[temp_cnt2]);
            temp_cnt2 += 1;
            if (temp_cnt2 == ncx) {
              break;
            };
            if (searched[temp_cnt2] == '}' & searched[temp_cnt2 - 1] != '\\') {
              cur_searched.push_back('}');
              break;
            };
          };
        } else {
          cur_par = 1;
          cur_break_ptrn = "";
          temp_cnt2 += 2;
          while (1) {
            if (searched[temp_cnt2] == '}' & searched[temp_cnt2 - 1] != '\\') {
              cur_par -= 1;
              if (cur_par == 0) {
                break;
              };
            } else if (searched[temp_cnt2] == '{' & searched[temp_cnt2 - 1] != '\\') {
              cur_par += 1;
            };
            cur_break_ptrn.push_back(searched[temp_cnt2]);
            temp_cnt2 += 1;
            if (temp_cnt2 == ncx) {
              break;
            };
          };
          cur_mp = regex_findr(cur_break_ptrn, cur_x);
          cur_it = cur_mp.begin();
          rslt_mp = cur_it->second.begin();
          if (rslt_mp->first) {
            idx_v = cur_it->first;
            rtn_pre_cnt = idx_v[0];
            cur_x = "";
            for (temp_cnt2 = 0; temp_cnt2 < rtn_pre_cnt; ++temp_cnt2) {
              cur_x.push_back(x[temp_cnt2]);
            };
          };
        };
      };
    };
    ncx = cur_x.length();
    cur_hmn_idxv = {};
    is_found = 0;
    while (1) {
      cur_mp = regex_findr1sub(cur_searched, cur_x);
      cur_it = cur_mp.begin();
      rslt_mp = cur_it->second.begin();
      if (rslt_mp->first) {
        is_found = 1;
        idx_v = cur_it->first;
        rtn_lst_cnt += idx_v[1];
        cur_hmn_idxv.push_back(rtn_lst_cnt);
        cur_str = rslt_mp->second;
      } else {
        break;
      };
      if (rtn_lst_cnt + 1 < ncx) {
        cur_x = "";
        for (temp_cnt2 = rtn_lst_cnt + 1; temp_cnt2 < ncx; ++temp_cnt2) {
          cur_x.push_back(x[temp_cnt2]);
        };
        rtn_lst_cnt += 1;
      } else {
        break;
      };
    };
    if (is_found) {
      hmn_idxv.push_back(cur_hmn_idxv);
      hmn_str_idxv.push_back(cur_str);
    };
  };
  return {{hmn_idxv, hmn_str_idxv}};
};


