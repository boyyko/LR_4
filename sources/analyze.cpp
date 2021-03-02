#include "analyze.hpp"
#include <iostream>
#include <algorithm>

using namespace  boost::filesystem;

file_system::file_system(const std::string path_to_file)
{
    _path_to_ftp = path(path_to_file);
    std::cout<<_path_to_ftp<<std::endl;
    if(is_symlink(_path_to_ftp))
        _path_to_ftp=read_symlink(_path_to_ftp);
    if(!is_directory(_path_to_ftp))
        throw std::runtime_error("This is not directory");
}

void file_system::check_all_path(path p, std::ostream &os)
{
    for (const directory_entry& x : directory_iterator{p})
  {
        if (is_directory(x.path()))
            check_all_path(x.path(), os);
        else if (is_regular_file(x.path()))
            to_process(x.path(), os);
    }
}

bool file_system::to_process(path p, std::ostream &os)
{
    if(check_file_name(p))
  {
        std::string file_name = p.filename().string();
        std::string account = check_account(file_name);
        std::string data = check_data(file_name);
        std::string broker = check_broker(p);

        if (account.size() == 0 || data.size() == 0 || broker.size() == 0)
            return false;

        os<<broker<<" "<<file_name<<std::endl;
        insert_element(account, data, broker);
        return true;
    }
    else
        return false;
}

bool file_system::check_file_name(path p)
{
  const std::string _txt = ".txt";
  const std::string _balance = "balance";

    if(p.extension()==_txt && p.filename().size() == len_name_file &&
       p.filename().string().substr(0, 7)==_balance)
        return true;
    else
        return false;
}

std::string file_system::check_account(std::string p)
{
    std::size_t iterator1 = p.find_first_of('_', 0);
    if(iterator1 == std::string::npos)  return std::string();
    ++iterator1;
    std::size_t iterator2 = p.find_last_of('_');
    if(iterator2 == std::string::npos) return std::string();
    std::string account = p.substr(iterator1, iterator2-iterator1);

    if(account.find_first_not_of(_numbers,0) != std::string::npos)
        return std::string();

    return account;
}

std::string file_system::check_data(std::string p)
{
    std::size_t iterator1 = p.find_last_of('_');
    if(iterator1 == std::string::npos) return std::string();
    ++iterator1;
    std::size_t iterator2 = p.find_last_of('.');
    if(iterator2 == std::string::npos) return std::string();
    std::string data = p.substr(iterator1, iterator2-iterator1);

    if(data.find_first_not_of(_numbers,0) != std::string::npos)
        return std::string();
    return data;
}

std::string file_system::check_broker(path p)
{
    p = absolute(p);
    std::size_t iterator2 = p.string().find_last_of('/');
    if(iterator2 == std::string::npos) return std::string();
    --iterator2;
    std::size_t iterator1 = p.string().find_last_of('/', iterator2);
    if(iterator1 == std::string::npos) return std::string();
    ++iterator1;
    ++iterator2;
    std::string broker = p.string().substr(iterator1, iterator2-iterator1);

    return broker;
}

void file_system::insert_element(std::string account, std::string data,std::string broker)
{
    std::vector<std::string>::iterator it = std::find(_account.begin(),_account.end(),account);
    std::vector<std::string>::difference_type index = std::distance
        (_account.begin(), it);
    if(_account.size() == (size_t) index)
    {
        _account.push_back(account);
        _broker.push_back(broker);
        _files.push_back(1);
        _last_date.push_back(std::stoi(data));
    }
    else if (_broker[index] == broker)
    {
        ++_files[index];
        _last_date[index] = (_last_date[index] > std::stoi(data))?
                           _last_date[index]:std::stoi(data);
    }
    else
    {
        throw std::runtime_error("Two owners per account");
    }
}

void file_system::show_acc(std::ostream &os)
{
    for (size_t i = 0; i < _account.size(); ++i)
  {
        os << "broker:" << _broker[i] << " account:" << _account[i] <<
          " files:" << _files[i] << " lastdate:" << _last_date[i] << std::endl;
    }
}

std::ostream& operator<<(std::ostream &os,  file_system& file_system)
{
    file_system.check_all_path(file_system._path_to_ftp, os);
    file_system.show_acc(os);
    return os;
}