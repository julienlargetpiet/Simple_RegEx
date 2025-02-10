#include<iostream>
#include<vector>
#include<map>

template <typename T, typename T2> unsigned int match(const std::vector<T> &source, const T2 &ptrn) {
  int cnt = 0;
  for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i) {
    if (*i == ptrn) {
      return cnt;
    };
    cnt += 1;
  };
  return -1;
};

template <typename T> std::vector<T> sort_ascout(const std::vector<T> &x) {
  std::vector<T> rtn = x;
  const unsigned int n = x.size();
  int i = 1;
  T ref;
  while (i < n) {
    if (rtn[i] < rtn[i - 1]) {
      ref = rtn[i];
      rtn[i] = rtn[i - 1];
      rtn[i - 1] = ref;
      if (i > 1) {
        i -= 1;
      } else {
        i += 1;
      };
    } else {
      i += 1;
    };
  };
  return rtn;
};

std::map<std::vector<unsigned int>, std::map<bool, std::string>> regex_findr2sub(std::string &searched, std::string &x) {
  char cur_chr;
  unsigned int i = 0;
  unsigned int cnt = 0;
  unsigned int ref_cnt;
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
  unsigned int cur_lmt;
  unsigned int ref_cur_lmt;
  unsigned int bf_rep_val;
  bool greedy_state1 = 0;
  bool greedy_state2 = 0;
  std::vector<unsigned int> ref_multiple_cnt = {};
  std::string cur_matched_str = "";
  std::string matched_str = "";
  std::string rtn_str;
  unsigned int lst_cnt;
  unsigned int pre_cnt;
  unsigned int cur_ref_cnt;
  unsigned int cur_ref_i;
  unsigned int temp_i;
  bool is_repetition = 0;
  bool alrd_zero = 0;
  std::vector<unsigned int> sorted_v;
  unsigned int cur_idx;
  unsigned int bf_cnt_zero = 0;
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
        while (searched[jump_i] != ']') {
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
        std::cout << "ref_int1: " << char(ref_int1) << " ref_int2: " << char(ref_int2) << "\n";
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
            cur_lmt = bf_rep_val + ref_rep_val;
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
            cur_lmt = bf_rep_val + ref_rep_val;
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
        matched_str += cur_matched_str;
        i = jump_i + 1;
        if (cur_matched_str != "") {
          lst_cnt = cnt - 1;
        } else {
          lst_cnt = cnt;
        };
        or_state = 0;
        greedy_state1 = 0;
        is_repetition = 0;
        ref_rep_val = 1;
      } else {
        if (i == jump_i2) {
          return {{{0, 0}, {{0, ""}}}};
        } else {
          cnt = ref_cnt;
        };
      };
    } else if (!cur_found) {
      return {{{0, 0}, {{0, ""}}}};
    } else {
      matched_str += cur_matched_str;
      if (cur_matched_str != "") {
        lst_cnt = cnt - 1;
      } else {
        lst_cnt = cnt;
      };
      is_repetition = 0;
      rep_val = 1;
    };
  };
  rtn_str = matched_str;
  pre_cnt = cnt - matched_str.length();
  return {{{pre_cnt, lst_cnt}, 
          {{cur_found, rtn_str}}}}; 
};

