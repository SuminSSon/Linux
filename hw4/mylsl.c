#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void ListFiles(char *path) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(path)) == NULL) { // path dir을open하여 반환된 포인터 저장
        perror("opendir");
        return;
    }

    printf("\n%s:\n", path); // 현재 dir 출력

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; // 현재 dir과 상위 dir 무시

        char mode;
        char perms[10];
        struct passwd *pwd; // 사용자 정보 구조체
        struct group *grp; // 그룹 정보 구조체
        struct tm *tm_info; // 시간 정보 구조체
        char mod_time[20]; // 파일 수정 시간

        if (lstat(entry->d_name, &statbuf) < 0) { // entry 파일 상태를 statbuf에 저장 
            perror("lstat");
            continue;
        }

        mode = S_ISDIR(statbuf.st_mode) ? 'd' : '-'; // 파일 유형 결정
        snprintf(perms, sizeof(perms), "%c%c%c%c%c%c%c%c%c", // 파일 권한 문자열 
                 (statbuf.st_mode & S_IRUSR) ? 'r' : '-',
                 (statbuf.st_mode & S_IWUSR) ? 'w' : '-',
                 (statbuf.st_mode & S_IXUSR) ? 'x' : '-',
                 (statbuf.st_mode & S_IRGRP) ? 'r' : '-',
                 (statbuf.st_mode & S_IWGRP) ? 'w' : '-',
                 (statbuf.st_mode & S_IXGRP) ? 'x' : '-',
                 (statbuf.st_mode & S_IROTH) ? 'r' : '-',
                 (statbuf.st_mode & S_IWOTH) ? 'w' : '-',
                 (statbuf.st_mode & S_IXOTH) ? 'x' : '-');

        printf("%c%s %ld ", mode, perms, (long)statbuf.st_nlink); // 파일 유형, 권한, 링크 수 출력

        pwd = getpwuid(statbuf.st_uid); // 파일 소유자 정보 가져오기
        grp = getgrgid(statbuf.st_gid); // 파일 그룹 정보 가져오기
        printf("%s %s %5ld ", pwd->pw_name, grp->gr_name, (long)statbuf.st_size); // 사용자, 그룹, 파일 크기 출력

        tm_info = localtime(&statbuf.st_mtime); // 파일 수정 시간 가져오기
        strftime(mod_time, sizeof(mod_time), "%b %d %H:%M", tm_info); //  시간 문자열 생성
        printf("%s ", mod_time); // 시간 출력

        if (S_ISLNK(statbuf.st_mode)) { // st_mode가 symbolic link인지 확인
            char linkname[1024];
            ssize_t len = readlink(entry->d_name, linkname, sizeof(linkname) - 1); // entry->d_name의 symbolic link 대상 경로를 읽어옴
            if (len != -1) {
                linkname[len] = '\0'; // 문자열 끝에 NULL 추가
                printf("%s -> %s\n", entry->d_name, linkname); // symbolic link 파일의 이름과 대상 경로 출력
            } else {
                perror("readlink");
                printf("%s\n", entry->d_name);
            }
        } else {
            printf("%s\n", entry->d_name); 
        }
    }

    closedir(dp);
}

int main() {
    ListFiles(".");
    return 0;
}

