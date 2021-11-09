# include <windows.h>
# include <iostream>
# include <vector>

# define DISK_NAME_SIZE 4

using namespace std;

struct DiskInfo { // out disk structure
    TCHAR name[DISK_NAME_SIZE];
    DWORD system_flags;
    DWORD serial_number;
    TCHAR file_system[10];
    __int64 total_space;
    __int64 free_space;
};

//обьявления методов, реализация под мейном
vector<DiskInfo> getDisksInfo();

void printInfo(vector<DiskInfo> vector);

int main(int argc, char** argv) {
    vector<DiskInfo> info = getDisksInfo();
    printInfo(info);
}

void printInfo(vector<DiskInfo> vector) { // print info
    for (auto& i : vector) {
        cout << "Disk name : \t\t" << i.name << endl;
        cout << "System flags : \t\t" << i.system_flags << endl;
        cout << "Serial number : \t" << i.serial_number << endl;
        cout << "File system : \t\t" << i.file_system << endl;
        cout << "Total space : \t\t" << i.total_space / (1024 * 1024) << " MB" << endl;
        cout << "Free space : \t" << i.free_space / (1024 * 1024) << " MB" << endl << endl;
    }
}

vector<DiskInfo> getDisksInfo() {
    auto* disk_names_arr = new TCHAR;
    //If the function succeeds, the return value is the length, in characters, of the strings copied to the buffer, not including the terminating null character.
    int disks_num = GetLogicalDriveStrings(MAXINTATOM, disk_names_arr) / DISK_NAME_SIZE;
    vector<DiskInfo> disks_info_queue; // vector of all disks info
    for (int i = 0; i < disks_num; ++i) {
        DiskInfo* disk_info = new DiskInfo(); // temp variable for info
        strcpy(disk_info->name, disk_names_arr); // copy name
        GetVolumeInformation(disk_info->name, NULL, 0, &disk_info->serial_number, 0, &disk_info->system_flags, // getting volume info
                             disk_info->file_system, sizeof(disk_info->file_system));
        GetDiskFreeSpaceEx(disk_info->name, (PULARGE_INTEGER)&disk_info->free_space,  // getting volume memory info
                           (PULARGE_INTEGER)&disk_info->total_space, NULL);
        disks_info_queue.push_back(*disk_info); // adding to list
        disk_names_arr += sizeof(TCHAR) * DISK_NAME_SIZE; // next volume
    }
    return disks_info_queue;
}
