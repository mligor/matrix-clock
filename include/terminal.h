#ifndef TERMINAL_H
#define TERMINAL_H

#include <Arduino.h>
#include <map>
#include <functional>

//TODO: extend the class to parse parameters from commands (e.g. echo mligor)
class Terminal
{
  public:
	void begin();
	void loop();

  protected:
	using Fn = std::function<void()>;
	using FnMap = std::map<String, Fn>;

	Terminal &on(const char *command, const Fn fn);

  private:
	FnMap m_commands;
};

extern Terminal terminal;

#endif // TERMINAL_COMMANDS_H
