// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <ostream>
#include <iostream>

using namespace boost;

class account
{
 public:
  std::string broker_name;
  std::vector<std::string> file_name;
  std::string number_account;
  std::string date;
};

class analyze {
 public:
  friend std::ostream &operator<<(std::ostream &os, const analyze &acc);
  void parse_dir_info(const filesystem::path&path_dir, const std::string &broker);
  std::string get_number_account(const std::string &filename);
  bool check_filename(const filesystem::path&path_file);
  std::string get_date(const std::string& filename) const;
  void set_lastdates();
  analyze(const filesystem::path &_path_ftp);
  ~analyze();
 private:
  filesystem::path path_ftp;
  std::vector<class account*> accounts;
};

std::ostream &operator<<(std::ostream &os, const account &acc);

#endif // INCLUDE_HEADER_HPP_
