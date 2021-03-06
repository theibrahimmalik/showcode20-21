#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <vector>

bool is_username_char(char c)
{
    return isalnum(c) || (c == '-') || (c == '_');
}

const char* find_next_username(const char* begin, const char* const end, std::string& out)
{
    while (true)
    {
        // get character after @
        begin = std::find(begin, end, '@');
        if (begin == end) { return begin; }
        ++begin;
        if (begin == end) { return begin; }
        // get next invalid character
        auto it_invalid = std::find_if_not(begin, end, is_username_char);
        // check if there were any valid characters
        auto size = std::distance(begin, it_invalid);
        if (size > 0)
        {
            out = std::string(begin, it_invalid);
            return begin;
        }
        else { begin = it_invalid; }
    }
}

std::string GetRecipient(const std::string& message, int position)
{
    const char* it = message.data();
    const char* end = it + message.size();

    std::string tmp;
    std::vector<std::string> usernames;

    do {
        it = find_next_username(it, end, tmp);
        if (tmp.empty()) { break; }
        else { usernames.push_back(tmp); tmp.clear(); }
    }
    while (it != end);

    if (position < 1 || (size_t)position > usernames.size()) { return ""; }
    else { return usernames[position - 1]; }
}
