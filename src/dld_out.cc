#include "dld_out.h"
#include "dld_lib.h"

DLD_Out::DLD_Out(const DLD_Out& cp) 
{
   init(cp);
}

DLD_Out::~DLD_Out() 
{
   DLDdbg << "Out " << path << " destructed" << endl;
   flush();
}

DLD_Out::DLD_Out(const string& _path)
{
   DLDdbg << "Out " << _path << " constructed" << endl;
   counter = new int;
   (*counter) = 1;
   out = new ofstream;
   out->open(_path.c_str());
   path = _path;
}

void DLD_Out::init(const DLD_Out& cp) const
{
   DLD_Out *pThis = const_cast<DLD_Out*>(this);
   pThis->out = cp.out;
   pThis->counter = cp.counter;
   (*pThis->counter)++;
   pThis->path = cp.path;
   DLDdbg << "Out " << path << " copied" << endl;
}

void DLD_Out::flush() const
{
   if(counter) {
      (*counter)--;
      if((*counter) == 0) {
	 DLD_Out *pThis = const_cast<DLD_Out*>(this);
	 DLDdbg << "Out " << path << " closed" << endl;
	 out->close();
	 unlink(path.c_str());
	 delete out;
	 delete counter;
	 pThis->out = 0;
	 pThis->counter = 0;
      }
   }
}

