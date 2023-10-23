#include <lua.hpp>
#include <stdio.h>  /* Mixing C and CPP headers, wonderful. */
#include <string>
#include <regex>
#define BUFMAX 256  /* hohoho */

void prompt(int);
void transform (char*);

/* Nicked from Roberto's PIL book, more or less */
int main(void)
{
	char buff[BUFMAX];
	int error = 0;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	prompt(error);  /* I wrote this line! */
	while (fgets(buff, sizeof(buff), stdin) != NULL)
	{
		transform(buff);  /* And this one! */
		error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
		if (error)
		{
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		prompt(error);
	}
	lua_close(L);
}

/* I wrote these functions! */
void prompt(int error){fputs(error ? ">:($ " : " :)$ ", stdout);}

void transform(char* buff)
{
	std::string tmp = buff;
	const std::string varExp = "[a-zA-Z0-9]+";
	const std::vector<std::pair<std::regex, std::string>> rules = {
		{
			std::regex("clear (" + varExp + ");"),
			std::string("$1 = 0;")
		},
		{
			std::regex("incr (" + varExp + ");"),
			std::string("$1 = $1 + 1;")
		},
		{
			std::regex("decr (" + varExp + ");"),
			std::string("if $1 ~= 0 then $1 = $1 - 1 end;")
		},
		{
			std::regex("copy (" + varExp + ") to (" + varExp + ");"),
			std::string("$2 = $1;")
		},
        {
			std::regex("while (" + varExp + ") not 0 do;"),
			std::string("while $1 ~=0 do")
		},
        {
			std::regex("buggeroff;"),
		    std::string("print(\"you could've just asked :'(\"); os.exit();")
		},
		{
			std::regex("init (" + varExp + ") = ([0-9]+);"),
			std::string("$1 = $2;")
		}
	};

	for (const auto& rule : rules)
		tmp = std::regex_replace(tmp, rule.first, rule.second);
	for (int buffLoc = 0; buffLoc < BUFMAX; buff[buffLoc++] = '\0');
	tmp.copy(buff, BUFMAX);
}
#undef BUFMAX
