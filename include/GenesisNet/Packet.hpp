#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <any>

namespace genesis {
	class Packet {
	public:
		Packet();

		explicit operator bool() const;

		Packet& operator>>(bool& d);
		Packet& operator>>(int8_t& d);
		Packet& operator>>(uint8_t& d);
		Packet& operator>>(int16_t& d);
		Packet& operator>>(uint16_t& d);
		Packet& operator>>(int32_t& d);
		Packet& operator>>(uint32_t& d);
		Packet& operator>>(int64_t& d);
		Packet& operator>>(uint64_t& d);
		Packet& operator>>(float& d);
		Packet& operator>>(double& d);
		Packet& operator>>(char* d);
		Packet& operator>>(std::string& d);

		Packet& operator<<(bool d);
		Packet& operator<<(int8_t d);
		Packet& operator<<(uint8_t d);
		Packet& operator<<(int16_t d);
		Packet& operator<<(uint16_t d);
		Packet& operator<<(int32_t d);
		Packet& operator<<(uint32_t d);
		Packet& operator<<(int64_t d);
		Packet& operator<<(uint64_t d);
		Packet& operator<<(float d);
		Packet& operator<<(double d);
		Packet& operator<<(const char* d);
		Packet& operator<<(const std::string& d);
		Packet& operator<<(const Packet& d);

		/**
		 * @brief Checks if the current read pos is the last
		 * @return true 
		 * @return false 
		 */
		bool isEnd() const;
		/**
		 * @brief Gets the size of this packet
		 * @return size_t 
		 */
		size_t getSize() const;
		/**
		 * @brief Gets the raw data of this packet
		 * @return const void* 
		 */
		const void* getData() const;
		/**
		 * @brief Checks if the extracting size not exceeds the data size
		 * @param size The size
		 * @return true 
		 * @return false 
		 */
		bool checkSize(size_t size);

		virtual const void* onSend(size_t& size);
		virtual void onReceive(const void* data, size_t size);
	private:
		/**
		 * @brief Appends data into the packet
		 * @param data the data
		 * @param bytes the size in bytes
		 */
		void append(const void* data, size_t bytes);

		size_t readPos;
		size_t sendPos;
		bool valid;
		std::vector<char> data;
	};
}
