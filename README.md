# Simple_RegEx

## First RegEx flavor

This flavor allows basic RegEx features as the 

- **or context** which is the set of elements that are inside `[]`, evaluates the expression from left to right 
- **range elements** matches every elements that are between `x-y` acording to the ASCII table
- **repetition** is the number of times a set of elements have to be matched, this is declared inside `{n}` after the set of elements
- **greedyness** allows to match a given number of times a set of elements or more, this is declared by `{+n}` after the set of elements

### Usage

`regex_findr(std::string &searched, std::string &x)`

- searched is the RegEx expression
- x is the string to search in

## Examples

```
std::string inpt_str = "uouuupeieeeppppiimi";
std::string searched = "[u{1}p{2}]{2}ii[a-em]";
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findr(searched, inpt_str);
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
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findr(searched, inpt_str);
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
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findr(searched, inpt_str);
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
std::map<std::vector<unsigned int>, std::map<bool, std::string>> outmp = regex_findr(searched, inpt_str);
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

