#include "layer3.h"

//@T regex_findrmid
//@U std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt; regex_findrmid(std::string searched, std::string x)
//@X
//@D ReGex dialect that handles break patterns declared as <code>{?pattern}</code>.
//@A searched : is the searche string
//@A x : is the string to search in
//@X
//@E std::string inpt_str = "uuppplchhdcpdedmepp";
//@E std::string searched = "[u{1}]{2}p{3}[lpm]{?p{3}}chh{?mepp}d{?mepp}";
//@E std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt; outmp = regex_findrmid(searched, inpt_str);
//@E std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt;::iterator it = outmp.begin();
//@E std::vector&lt;int&gt; vec1 = it-&gt;first;
//@E std::map&lt;bool, std::string&gt;::iterator it2b = it-&gt;second.begin();
//@E std::cout &lt;&lt; vec1[0] << "\n";
//@E std::cout &lt;&lt; vec1[1] << "\n";
//@E std::cout &lt;&lt; it2b->first << "\n";
//@E std::cout &lt;&lt; it2b->second << "\n";
//@E 0
//@E 9
//@E 1
//@E "uuppplchhd"
//@E inpt_str = "uouuupeieeeppppiimiooo";
//@E searched = "[p]{4}i{?ooo}i[a-zm]";
//@E outmp = regex_findrmid(searched, x);
//@E it = outmp.begin();
//@E vec1 = it-&gt;first;
//@E it2b = it-&gt;second.begin();
//@E vec1[0] << "\n";
//@E vec1[1] << "\n";
//@E it2b->first << "\n";
//@E it2b->second << "\n";
//@E 11
//@E 17
//@E 1
//@E "ppppiim"
//@X

std::map<std::vector<int>, std::map<bool, std::string>> regex_findrmid(std::string &searched, std::string &x) {
  std::string cur_searched = "";
  std::string cur_cur_searched = "";
  std::string cur_x = x;
  std::string cur_x_ref;
  std::string rtn_str;
  std::string cur_str;
  std::string cur_break_ptrn = "";
  std::string cur_rslt;
  bool ok_next;
  bool is_mult;
  unsigned int idx_condition;
  unsigned int cnt = 0;
  unsigned int cnt2;
  unsigned int temp_cnt;
  unsigned int jump_cnt;
  unsigned int ref_mult;
  int rtn_lst_cnt = -1;
  unsigned int rtn_pre_cnt;
  bool agn = 1;
  unsigned int cur_hmn = 0;
  unsigned int cur_hmn_idx = 0;
  bool or_context = 0;
  std::map<std::vector<unsigned int>, std::map<bool, std::string>> cur_mp;
  std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator cur_it;
  std::map<bool, std::string>::iterator rslt_mp;
  std::vector<unsigned int> idx_v;
  const unsigned int n = searched.length();
  unsigned int n2 = x.length();
  const unsigned int n2_ref = n2;
  unsigned int n_hmn;
  unsigned int cur_par;
  unsigned int ref_cnt;
  unsigned int conditions_idx;
  std::vector<unsigned int> conditions_idxv2;
  if (searched[0] == '[') {
    cnt = 1;
    while (searched[cnt] != ']') {
      cnt += 1;
    };
  } else if (cnt + 1 < n) {
    if (searched[cnt + 1] == '-') {
      cnt += 2;
    };
  };
  if (cnt + 1 < n) {
    cnt += 1;
    if (searched[cnt] == '{') {
      cnt += 1;
      if (searched[cnt] == '?') {
        cur_break_ptrn = "";
        cnt += 1;
        cur_par = 1;
        while (1) {
          if (searched[cnt] == '}' & searched[cnt - 1] != '\\') {
            cur_par -= 1;
            if (cur_par == 0) {
              break;
            };
          } else if (searched[cnt] == '{' & searched[cnt - 1] != '\\') {
            cur_par += 1; 
          };
          cur_break_ptrn.push_back(searched[cnt]);
          cnt += 1;
        };
        cur_mp = regex_findrlow(cur_break_ptrn, cur_x);
        cur_it = cur_mp.begin();
        rslt_mp = cur_it->second.begin();
        if (rslt_mp->first) {
          idx_v = cur_it->first;
          rtn_lst_cnt = idx_v[1];
          for (cnt2 = 0; cnt2 < n2 - rtn_lst_cnt - 1; ++cnt2) {
            cur_x.pop_back();
          };
        };
      };
    };
  };
  std::map<std::vector<std::vector<unsigned int>>, std::vector<std::vector<std::string>>> bgn_mp = regex_findr_bgn_mid(searched, cur_x);
  std::map<std::vector<std::vector<unsigned int>>, std::vector<std::vector<std::string>>>::iterator bgn_it = bgn_mp.begin();
  std::vector<std::vector<std::string>> hmn_str_idxv = bgn_it->second;
  std::vector<std::vector<unsigned int>> hmn_idxv = bgn_it->first;
  rtn_str = hmn_str_idxv[0][0];
  cnt = regex_findr_first_condition_idx(searched);
  ref_cnt = cnt;
  rtn_lst_cnt = hmn_idxv[0][0];
  n_hmn = hmn_idxv.size();
  cur_x = "";
  for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
    cur_x.push_back(x[cnt2]);
  };
  while (cnt < n) {
    if (searched[cnt] == '{' & searched[cnt - 1] != '\\') {
      cnt += 1;
      if (searched[cnt] == '?') {
        ok_next = 1;
        cnt += 1;
        cur_break_ptrn = "";
        cur_x = "";
        cur_par = 1;
        while (1) {
          if (searched[cnt] == '{' & searched[cnt] != '\\') {
            cur_par += 1;
          } else if (searched[cnt] == '}' & searched[cnt] != '\\') {
            cur_par -= 1;
            if (cur_par == 0) {
              break;
            };
          };
          cur_break_ptrn.push_back(searched[cnt]);
          cnt += 1;
        };
        cnt += 1;
        for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
          cur_x.push_back(x[cnt2]);
        };
        cur_cur_searched = cur_searched[cur_searched.length() - 1];
        cur_searched.pop_back();
        if (cur_searched.length() > 1) {
          if (cur_searched[cur_searched.length() - 1] == '-' & cur_searched[cur_searched.length() - 1] != '\\') {
            cur_cur_searched.insert(0, 1, '-');
            cur_searched.pop_back();
            cur_cur_searched.insert(0, 1, cur_searched[cur_searched.length() - 1]);
            cur_searched.pop_back();
          };
        };
        if (cur_searched.length() > 0) {
          cur_mp = regex_findr2sub(cur_searched, cur_x);
          cur_it = cur_mp.begin();
          rslt_mp = cur_it->second.begin();
          if (rslt_mp->first) {
            idx_v = cur_it->first;
            cur_str = rslt_mp->second;
            rtn_str += cur_str;
            rtn_lst_cnt += cur_str.length();
            cur_x = "";
            for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
              cur_x.push_back(x[cnt2]);
            };
          } else {
            ok_next = 0;
            cur_hmn_idx += 1;
            cnt = ref_cnt;
            if (cur_hmn_idx == hmn_idxv[cur_hmn].size()) {
              cur_hmn_idx = 0;
              cur_hmn += 1;
              if (cur_hmn < n_hmn) {
                rtn_str = hmn_str_idxv[cur_hmn][cur_hmn_idx];
                rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
              } else {
                return {{{0, 0}, {{0, ""}}}};
              };
            } else {
              rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
            };
          };
        };
        cur_mp = regex_findrlow(cur_break_ptrn, cur_x);
        cur_it = cur_mp.begin();
        rslt_mp = cur_it->second.begin();
        if (rslt_mp->first) {
          idx_v = cur_it->first;
          rtn_pre_cnt = idx_v[0];
          cur_x_ref = cur_x;
          cur_x = "";
          for (temp_cnt = 0; temp_cnt < rtn_pre_cnt; ++temp_cnt) {
            cur_x.push_back(cur_x_ref[temp_cnt]);
          };
        };
        cur_mp = regex_findr2sub(cur_cur_searched, cur_x);
        cur_it = cur_mp.begin();
        rslt_mp = cur_it->second.begin();
        if (rslt_mp->first) {
          cur_str = rslt_mp->second;
          rtn_lst_cnt += cur_str.length(); 
          rtn_str += cur_str;
          if (or_context) {
            cnt = jump_cnt;
            or_context = 0;
            is_mult = 0;
            n2 = n2_ref;
          };
        } else if (ok_next) {
          if (or_context) {
            if (cnt < conditions_idx) {
              ok_next = 0;
            };
          };
          if (ok_next) {
            cur_hmn_idx += 1;
            cnt = ref_cnt;
            if (cur_hmn_idx == hmn_idxv[cur_hmn].size()) {
              cur_hmn_idx = 0;
              cur_hmn += 1;
              if (cur_hmn < n_hmn) {
                rtn_str = hmn_str_idxv[cur_hmn][cur_hmn_idx];
                rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
              } else {
                return {{{0, 0}, {{0, ""}}}};
              };
            } else {
              rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
            };
          };
        };
        cur_searched = "";
      } else {
        cur_searched.push_back('{');
      };
    } else if (or_context) {
      if (conditions_idxv2.size() > 0) {
        if (cnt - 1 == conditions_idxv2[idx_condition]) {
          
          cur_cur_searched = cur_searched[cur_searched.length() - 1];
          cur_searched.pop_back();
          if (cur_searched.length() > 1) {
            if (cur_searched[cur_searched.length() - 1] == '-') {
              cur_cur_searched.insert(0, 1, '-');
              cur_searched.pop_back();
              cur_cur_searched.insert(0, 1, cur_searched[cur_searched.length() - 1]);
              cur_searched.pop_back();
            };
          };
          ok_next = 1;
          if (cur_searched.length() > 0) {
            cur_mp = regex_findr2sub(cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              cur_str = rslt_mp->second;
              rtn_str += cur_str;
              rtn_lst_cnt += cur_str.length();
              cur_x = "";
              for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
                cur_x.push_back(x[cnt2]);
              };
            } else {
              ok_next = 0;
              cur_hmn_idx += 1;
              cnt = ref_cnt;
              if (cur_hmn_idx == hmn_idxv[cur_hmn].size()) {
                cur_hmn_idx = 0;
                cur_hmn += 1;
                if (cur_hmn < n_hmn) {
                  rtn_str = hmn_str_idxv[cur_hmn][cur_hmn_idx];
                  rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
                } else {
                  return {{{0, 0}, {{0, ""}}}};
                };
              } else {
                rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
              };
            };
            cur_searched = "";
          };
          if (ok_next) {
            idx_condition += 1;
            cur_cur_searched.insert(0, 1, '[');
            cur_cur_searched.push_back(']');
            cur_cur_searched.push_back('{');
            cur_cur_searched += std::to_string(ref_mult);
            cur_cur_searched.push_back('}');
            cur_x = "";
            for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
              cur_x.push_back(x[cnt2]);
            };
            cur_mp = regex_findr2sub(cur_cur_searched, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              cur_str = rslt_mp->second;
              rtn_str += cur_str;
              rtn_lst_cnt += cur_str.length();
              cur_x = "";
              n2 = n2_ref;
              for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
                cur_x.push_back(x[cnt2]);
              };
              cnt = jump_cnt;
              or_context = 0;
              is_mult = 0;
            } else {
              if (cnt == conditions_idx) {
                cur_hmn_idx += 1;
                cnt = ref_cnt;
                if (cur_hmn_idx == hmn_idxv[cur_hmn].size()) {
                  cur_hmn_idx = 0;
                  cur_hmn += 1;
                  if (cur_hmn < n_hmn) {
                    rtn_str = hmn_str_idxv[cur_hmn][cur_hmn_idx];
                    rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
                  } else {
                    return {{{0, 0}, {{0, ""}}}};
                  };
                } else {
                  rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
                };
              };
            };
          };
        };
      };
    } else if (searched[cnt] == '[' & searched[cnt - 1] != '\\') {
      idx_condition = 0;
      is_mult = 0;
      conditions_idxv2 = {};
      temp_cnt = cnt + 1;
      or_context = 1;
      ref_mult = 1;
      while (1) {
        if (searched[temp_cnt] == ']' & searched[temp_cnt - 1] != '\\') {
          break;
        } else if (searched[temp_cnt + 1] == '{' & searched[temp_cnt] != '\\') {
           temp_cnt += 1;
           if (searched[temp_cnt + 1] != '?') {
             temp_cnt += 1;
             while (searched[temp_cnt] != '}') {
               temp_cnt += 1;
             };
             conditions_idxv2.push_back(temp_cnt);
           } else {
             temp_cnt += 1;
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
               temp_cnt += 1;
             };
           };
        } else {
          if (searched[temp_cnt + 1] == '-') {
            temp_cnt += 2;
          };
          conditions_idxv2.push_back(temp_cnt);
        };
        temp_cnt += 1;
      };
      conditions_idx = temp_cnt;
      temp_cnt += 1;
      if (temp_cnt < n) {
        if (searched[temp_cnt] == '{') {
          temp_cnt += 1;
          if (searched[temp_cnt] == '?') {
            cur_break_ptrn = "";
            temp_cnt += 1;
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
              cur_break_ptrn.push_back(searched[temp_cnt]);
              temp_cnt += 1;
            };
            cur_mp = regex_findrlow(cur_break_ptrn, cur_x);
            cur_it = cur_mp.begin();
            rslt_mp = cur_it->second.begin();
            if (rslt_mp->first) {
              idx_v = cur_it->first;
              n2 = idx_v[0];
            };
            temp_cnt += 1;
          } else {
            is_mult = 1;
            ref_mult = int(searched[temp_cnt]) - 48;
            while (searched[temp_cnt] != '}') {
              ref_mult *= 10;
              ref_mult += (int(searched[temp_cnt]) - 48);
              temp_cnt += 1;
            };
            temp_cnt += 1;
          };
        };
      };
      cnt += 1;
      jump_cnt = temp_cnt;
    };
    if (cnt < n) {
      cur_searched.push_back(searched[cnt]);
      cnt += 1;
    };
  };
  if (cur_searched.length() > 0) {
    while (1) {
      cur_x = "";
      for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
        cur_x.push_back(x[cnt2]);
      };
      cur_mp = regex_findr2sub(cur_searched, cur_x);
      cur_it = cur_mp.begin();
      rslt_mp = cur_it->second.begin();
      if (rslt_mp->first) {
        cur_str = rslt_mp->second;
        rtn_str += cur_str;
        rtn_lst_cnt += cur_str.length();
        break;
      };
      cur_hmn_idx += 1;
      cnt = ref_cnt;
      if (cur_hmn_idx == hmn_idxv[cur_hmn].size()) {
        cur_hmn_idx = 0;
        cur_hmn += 1;
        if (cur_hmn < n_hmn) {
          rtn_str = hmn_str_idxv[cur_hmn][cur_hmn_idx];
          rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
        } else {
          return {{{0, 0}, {{0, ""}}}};
        };
      } else {
        rtn_lst_cnt = hmn_idxv[cur_hmn][cur_hmn_idx];
      };
    };
  };
  rtn_pre_cnt = rtn_lst_cnt - rtn_str.length() + 1;
  return {{{(int)rtn_pre_cnt, rtn_lst_cnt}, {{1, rtn_str}}}};
};


