#pragma once
#define PROGRESS_NOFLUSH(x,y) std::cout<<"\r"<<x<<":"<<y
#define PROGRESS(x,y) PROGRESS_NOFLUSH(x,y)<<' '<<std::flush;
#define PROGRESS_PERCENTAGE(x,y,ymax) PROGRESS_NOFLUSH(x,static_cast<int>(100.0*static_cast<double>(y)/static_cast<double>(ymax)) )<<"%"<<' '<<std::flush
#define PROGRESS_COMPLETE std::cout<<"\nDone.\n";