#include <GenesisNet/Packet.hpp>
#include <WinSock2.h>

namespace genesis {
	Packet::Packet(): readPos(0), sendPos(0), valid(true) {
	}

	bool Packet::isEnd() const {
		return this->readPos >= this->data.size();
	}
	size_t Packet::getSize() const {
		return this->data.size();
	}
	Packet::operator bool() const {
		return this->valid;
	}
	const void* Packet::getData() const {
		return this->data.empty() ? nullptr : this->data.data();
	}
	bool Packet::checkSize(size_t size) {
		this->valid = this->valid && (this->readPos + size <= this->data.size());
		return valid;
	}

	Packet& Packet::operator>>(bool& d) {
		uint8_t v;
		if(*this >> v) {
			d = (v != 0);
		}
		return *this;
	}
	Packet& Packet::operator>>(int8_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(uint8_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(int16_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = static_cast<int16_t>(ntohs(static_cast<uint16_t>(d)));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(uint16_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = ntohs(d);
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(int32_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = static_cast<int32_t>(ntohl(static_cast<uint32_t>(d)));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(uint32_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = ntohl(d);
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(int64_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = static_cast<int64_t>(ntohll(static_cast<uint64_t>(d)));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(uint64_t& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			d = ntohll(d);
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(float& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(double& d) {
		if(checkSize(sizeof(d))) {
			std::memcpy(&d, &this->data[this->readPos], sizeof(d));
			this->readPos += sizeof(d);
		}
		return *this;
	}
	Packet& Packet::operator>>(char* d) {
		uint32_t length = 0;
		*this >> length;
		if(length > 0 && checkSize(length)) {
			std::memcpy(d, &this->data[this->readPos], length);
			data[length] = '\0';
			this->readPos += length;
		}
		return *this;
	}
	Packet& Packet::operator>>(std::string& d) {
		uint32_t length = 0;
		*this >> length;
		d.clear();
		if(length > 0 && checkSize(length)) {
			d.assign(&this->data[this->readPos], length);
			this->readPos += length;
		}
		return *this;
	}

	Packet& Packet::operator<<(bool d) {
		*this << static_cast<uint8_t>(d);
		return *this;
	}
	Packet& Packet::operator<<(int8_t d) {
		append(&d, sizeof(d));
		return *this;
	}
	Packet& Packet::operator<<(uint8_t d) {
		append(&d, sizeof(d));
		return *this;
	}
	Packet& Packet::operator<<(int16_t d) {
		auto toWrite = static_cast<int16_t>(htons(static_cast<uint16_t>(d)));
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(uint16_t d) {
		auto toWrite = htons(d);
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(int32_t d) {
		auto toWrite = static_cast<int32_t>(htonl(static_cast<uint32_t>(d)));
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(uint32_t d) {
		auto toWrite = htonl(d);
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(int64_t d) {
		auto toWrite = static_cast<int64_t>(htonll(static_cast<uint64_t>(d)));
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(uint64_t d) {
		auto toWrite = htonll(d);
		append(&toWrite, sizeof(toWrite));
		return *this;
	}
	Packet& Packet::operator<<(float d) {
		append(&d, sizeof(d));
		return *this;
	}
	Packet& Packet::operator<<(double d) {
		append(&d, sizeof(d));
		return *this;
	}
	Packet& Packet::operator<<(const char* d) {
		auto length = static_cast<uint32_t>(std::strlen(d));
		*this << length;
		append(d, length * sizeof(char));
		return *this;
	}
	Packet& Packet::operator<<(const std::string& d) {
		auto length = static_cast<uint32_t>(d.size());
		*this << length;
		if(length > 0) {
			append(d.c_str(), length * sizeof(std::string::value_type));
		}
		return *this;
	}
	Packet& Packet::operator<<(const Packet& d) {
		append(d.getData(), d.getSize());
		return *this;
	}

	void Packet::append(const void* data, size_t bytes) {
		if(data && bytes > 0) {
			size_t start = this->data.size();
			this->data.resize(start + bytes);
			std::memcpy(&this->data[start], data, bytes);
		}
	}

	const void* Packet::onSend(size_t& size) {
		size = getSize();
		return getData();
	}
	void Packet::onReceive(const void* data, size_t size) {
		append(data, size);
	}
}
