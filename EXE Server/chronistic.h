// chronistic.h
struct Chronistic
{
Chronistic(int _seconds) : seconds(_seconds) {next(time(0));}
virtual bool operator()() = 0; // pure virtural, never call from c'tor or d'tor
private: int seconds;
protected:
bool trigger()
{
time_t now = time(0);
if (now > trigger_target) return next(now); // always true
else return false;
}
private:
time_t trigger_target;
bool next(time_t now) // must not be virtual, must not call anything virtual (it's used in the c'tor). Always returns true.
{
trigger_target=now+seconds;
return true;
}
};
