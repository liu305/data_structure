#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector<std::pair<long long,int>> nft_n_index_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void SiftDown(int i)
  {
    int minIndex = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if (left < nft_n_index_.size() && ((nft_n_index_[left].first < nft_n_index_[minIndex].first) || (nft_n_index_[left].first == nft_n_index_[minIndex].first && nft_n_index_[left].second < nft_n_index_[minIndex].second))) {minIndex = left;}
    if (right < nft_n_index_.size() && ((nft_n_index_[right].first < nft_n_index_[minIndex].first) || (nft_n_index_[right].first == nft_n_index_[minIndex].first && nft_n_index_[right].second < nft_n_index_[minIndex].second))) {minIndex = right;}
    if ( i != minIndex) { std::swap(nft_n_index_[i],nft_n_index_[minIndex]); SiftDown(minIndex); }
  }

  void SiftUp(int i)
  {
    while (i>0 && (nft_n_index_[(i-1)/2].first > nft_n_index_[i].first || (nft_n_index_[(i-1)/2].first == nft_n_index_[i].first && nft_n_index_[(i-1)/2].second > nft_n_index_[i].second))) {
      std::swap(nft_n_index_[(i-1)/2],nft_n_index_[i]);
      i=(i-1)/2;
    }  
  }

  void AssignJobs() {

    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    nft_n_index_.resize(num_workers_);
    for (int i = 0; i < num_workers_; ++i)
    {
       nft_n_index_[i].first=0;
       nft_n_index_[i].second=i;
    }
    for (int i = 0; i < jobs_.size(); ++i) {
      assigned_workers_[i] = nft_n_index_[0].second;
      start_times_[i] = nft_n_index_[0].first;
      nft_n_index_[0].first += jobs_[i];
      SiftDown(0);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
