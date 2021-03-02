// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_ANALYZE_HPP_
#define INCLUDE_ANALYZE_HPP_

#include <boost/filesystem.hpp>
#include <vector>

class file_system
{
 public:
  file_system(const std::string path_to_file);
  void check_all_path(boost::filesystem::path p, std::ostream &os);
  bool to_process(boost::filesystem::path p, std::ostream &os);
  bool check_file_name(boost::filesystem::path p);
  std::string check_account(std::string p);
  std::string check_data(std::string p);
  std::string check_broker(boost::filesystem::path p);
  void show_acc(std::ostream &os);
  void insert_element(std::string account, std::string data, std::string broker);
  friend std::ostream& operator<<(std::ostream &os, file_system& file_system);
 private:
  boost::filesystem::path _path_to_ftp;
  std::vector<std::string> _broker;
  std::vector<std::string> _account;
  std::vector<long int> _files;
  std::vector<long int> _last_date;

  const size_t len_name_file = 29;
  const std::string _numbers = "0123456789";
};
#endif // INCLUDE_ANALYZE_HPP_
