#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "commons.hpp"
#include "ecsdb.hpp"
#include <map>
#include <iostream>

/** \brief 파일을 읽어오는 매니저 클래스
 *
 * 레벨에 따른 레벨 정보를 읽고 DB에 저장하는 클래스
 */
class FileManager{
private:
	/** \brief #으로 시작하는 주석을 읽은 뒤 버리는 함수
	 *
	 * @param f 파일을 읽고 있는 ifstream 객체
	 */
	void eat_comment(std::ifstream &f);

	/** \brief YAML로 작성된 레벨 파일을 읽는 함수
	 *
	 * @param file 읽고자 하는 파일 문자열
	 */
	void load_file(const std::string& file);

	/** \brief PPM 파일을 읽는 함수
	 *
	 * @param ppm 읽고자 하는 파일 문자열
	 */
	void load_ppm(const std::string& ppm);

	/** \brief 일은 파일의 정보를 db에 저장하는 함수
	 *
	 * @param 정보를 저장하고자 하는 db
	 */
	void update_db(ECSDB &db);

	/// 레벨의 지도 정보가 저장되어 있는 ppm 파일의 이름
	std::string ppm_name;
	/// 지도의 길이, 너비
	int width, height;
	/// 성공에 필요한 아이템 개수
	int growth_counter, poison_counter;
	/// 읽어온 최초 레벨의 문자 지도
	//char** color_map;
	std::vector<std::vector<char>> color_map;
	/// 처음 주어지는 뱀의 방향값
	int snake_direction;

	/// 레벨의 이름을 레벨 정수와 이어놓은 map 변수
	const std::map<int, std::string> level_name = {
		{1, "1.yml"},
		{2, "2.yml"},
		{3, "3.yml"},
		{4, "4.yml"},
		{5, "5.yml"}
	};

public:
	/** \brief 파일 매니저의 역할을 트리거 하는 함수
	 *
	 * @param level 불러오고자 하는 레벨의 정수 
	 * @param db 불러온 정보를 저장할 db값
	 */
	void process(int level, ECSDB &db);
};

#endif
