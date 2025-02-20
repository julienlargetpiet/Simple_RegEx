# Simple_RegEx

## First RegEx flavor

This minimalist RegEx flavor allows basic RegEx features such as:

- **or context** which is the set of elements that are inside `[]`, evaluates the expression from left to right 
- **range elements** matches every elements that are between `x-y` acording to the ASCII table
- **repetition** is the number of times a set of elements have to be matched, this is declared inside `{n}` after the set of elements
- **greedyness** allows to match a given number of times a set of elements or more, this is declared by `{+n}` after the set of elements
- '\\' is used to escape special characters, apart when it is in a range context, so `\\-x` or `x-\\` are valid

The rule of thumb is to not put same set of elements side to side as the first 2 conditions.

In **or context**, do not put set of elements that have commun elements. Convert them to multiple exactly different sets with no commun elements.

### Usage

`regex_findrmid(std::string &searched, std::string &x)`

- searched is the RegEx expression
- x is the string to search in

## Examples

```
std::string inpt_str = "uouuupeieeeppppiimi";
std::string searched = "[u{1}p{2}]{2}ii[a-em]";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator it = outmp.begin();
std::vector<unsigned int> vec1 = it->first;
std::map<bool, std::string>::iterator it2b = it->second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
11
17
1
ppppiim
```

```
std::string inpt_str = "uouuupeieeeppppiimi";
std::string searched = "[u{1}p{2}]{+1}ii[a-em]";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator it = outmp.begin();
std::vector<unsigned int> vec1 = it->first;
std::map<bool, std::string>::iterator it2b = it->second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
11
17
1
ppppiim
```

```
std::string inpt_str = "uouuupeieeeppppiimi";
std::string searched = "e{+1}p{2}";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator it = outmp.begin();
std::vector<unsigned int> vec1 = it->first;
std::map<bool, std::string>::iterator it2b = it->second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
8
12
1
eeepp
```

```
std::string inpt_str = "uouuupeieeeppppiimi";
std::string searched = "[a-ia-z]{+1}";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator it = outmp.begin();
std::vector<unsigned int> vec1 = it->first;
std::map<bool, std::string>::iterator it2b = it->second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
6
10
1
eieee
```

```
std::string inpt_str = "ouppplchdcpdedmePp";
std::string searched = "[mqp]{0}up{3}lchdy{+0}p{0}";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator it = outmp.begin();
std::vector<unsigned int> vec1 = it->first;
std::map<bool, std::string>::iterator it2b = it->second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
1
8
1
uppplchd
```

### Break patterns

Break patterns are used after a set of elements to significate their greedyness until it encounters a certain pattern. They are declared with `{?pattern}`

```
std::string inpt_str = "uuppplchhdcpdedmepp";
std::string searched = "[u{1}]{2}p{3}[lpm]{?p{3}}chh{?mepp}d{?mepp}";
std::map<std::vector<int<, std::map<bool, std::string<< outmp = regex_findrmid(searched, inpt_str);
std::map<std::vector<int<, std::map<bool, std::string<<::iterator it = outmp.begin();
std::vector<int< vec1 = it-<first;
std::map<bool, std::string<::iterator it2b = it-<second.begin();
std::cout << vec1[0] << "\n";
std::cout << vec1[1] << "\n";
std::cout << it2b->first << "\n";
std::cout << it2b->second << "\n";
```

```
0
9
1
"uuppplchhd"
```

```
inpt_str = "uouuupeieeeppppiimiooo";
searched = "[p]{4}i{?ooo}i[a-zm]";
outmp = regex_findrmid(searched, x);
it = outmp.begin();
vec1 = it-<first;
it2b = it-<second.begin();
vec1[0] << "\n";
vec1[1] << "\n";
it2b->first << "\n";
it2b->second << "\n";
```

```
11
17
1
"ppppiim"
```
