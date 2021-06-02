#pragma once
#define PROGRESS_CERR(x,y) std::cerr<<"\r"<<x<<":"<<y<<' '<<std::flush;
#define PROGRESS_CERR_COMPLETE std::cerr<<"\nDone.\n";