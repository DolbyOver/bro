// See the file "COPYING" in the main distribution directory for copyright.
// 
// Same notes about thread safety as in LogWriter.h apply.


#ifndef INPUTREADER_H
#define INPUTREADER_H

#include "InputMgr.h"
#include "BroString.h"
#include "LogMgr.h"

class InputReader {
public:
    InputReader();
    virtual ~InputReader();
	
	bool Init(string arg_source, int num_fields, const LogField* const* fields);
    
	void Finish();

	bool Update();
	
protected:
    // Methods that have to be overwritten by the individual readers
	virtual bool DoInit(string arg_source, int num_fields, const LogField* const * fields) = 0;
	
	virtual void DoFinish() = 0;

	// update file contents to logmgr
	virtual bool DoUpdate() = 0;
	
	// Reports an error to the user.
	void Error(const string &msg);
	void Error(const char *msg);
	
	// The following methods return the information as passed to Init().
	const string Source() const	{ return source; }

	// A thread-safe version of fmt(). (stolen from logwriter)
	const char* Fmt(const char* format, ...);

	void SendEvent(const string& name, const int num_vals, const LogVal* const *vals);

private:
    friend class InputMgr;
	
	string source;
	int num_fields;
	const LogField* const * fields;
    
    // When an error occurs, this method is called to set a flag marking the 
    // writer as disabled.
    
    bool disabled;
    
    bool Disabled() { return disabled; }

	// For implementing Fmt().
	char* buf;
	unsigned int buf_len;    
};


#endif /* INPUTREADER_H */
