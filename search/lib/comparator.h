
struct filenameComp{
	bool operator()(WebPage* wp1, WebPage* wp2){
			bool isLessThan = wp1->filename() <= wp2->filename();
			return isLessThan;
		}
};

struct incLinkSizeComp {
	bool operator()(WebPage* wp1, WebPage* wp2){
			bool isLessThan =  wp1->incoming_links().size() <= wp2->incoming_links().size() ; 
			return isLessThan;
	}
};

struct outgLinkSizeComp {
	bool operator()(WebPage* wp1, WebPage* wp2){
		bool isLessThan =  wp1->outgoing_links().size() <= wp2->outgoing_links().size() ;
		return isLessThan; 
	}
};

struct pageRankComp {
	bool operator()(std::pair<WebPage*, double> pair1, std::pair<WebPage*, double> pair2){
		bool isLessThan = pair1.second >= pair2.second;
		return isLessThan;
	}
};