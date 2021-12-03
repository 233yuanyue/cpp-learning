#pragma once
#include<iostream>
#include<cmath>

template<typename Ty = double>
class Complex
{
	template<typename Ty1>
	friend std::ostream& operator<<(std::ostream&, const Complex<Ty1>&);//如此定义就不会报错了
public:
	Complex() :mReal(Ty()), mImag(Ty()) {}
	Complex(Ty real, Ty imag = Ty()) :mReal(real), mImag(imag) {}
	Complex(const Complex &cpx) :mReal(cpx.mReal), mImag(cpx.mImag) {}
	Complex(Complex &&cpx) :mReal(cpx.mReal), mImag(cpx.mImag) {}

	Complex conjugate()const {
		return Complex(this->mReal, -this->mImag);
	}

	Ty real()const {
		return this->mReal;
	}

	Ty imag()const {
		return this->mImag;
	}

	double modulus()const {
		return std::sqrt(std::pow(this->mReal, 2) + std::pow(this->mImag, 2));
	}

	double argument()const {
		return std::tan(static_cast<double>(this->mImag) / static_cast<double>(this->mReal));
	}

	bool operator==(const Complex &cpx)const
	{
		return this->mReal == cpx.mReal
			&& this->mImag == cpx.mImag;
	}
	bool operator==(Complex &&cpx)const {
		return this->mReal == cpx.mReal
			&& this->imag == cpx.imag;
	}
	bool operator==(const Ty &ty)const {
		return this->mReal == ty
			&& this->mImag == Ty();
	}
	bool operator==(Ty &&ty)const {
		return this->mReal == ty
			&& this->mImag == Ty();
	}

	bool operator!=(const Complex &cpx)const
	{
		return !(this->operator==(cpx));
	}
	bool operator!=(Complex &&cpx)const {
		return !(this->operator==(cpx));
	}
	bool operator!=(const Ty &ty)const {
		return !(this->operator==(ty));
	}
	bool operator!=(Ty &&ty)const {
		return !(this->operator==(ty));
	}

	bool operator>(const Complex &cpx)const {
		return this->modulus()
			> cpx.modulus();
	}
	bool operator>(Complex &&cpx)const {
		return this->modulus()
			> cpx.modulus();
	}
	bool operator>(const Ty &ty)const {
		return this->modulus() > ty;
	}
	bool operator>(Ty &&ty)const {
		return this->modulus > ty;
	}

	bool operator>=(const Complex &cpx)const {
		return this->operator==(cpx)
			&& this->operator>(cpx);
	}
	bool operator>=(Complex &&cpx)const {
		return this->operator==(cpx)
			&& this->operator>(cpx);
	}
	bool operator>=(const Ty &ty)const {
		return this->operator==(ty)
			&& this->operator>(ty);
	}
	bool operator>=(Ty &&ty)const {
		return this->operator==(ty)
			&& this->operator>(ty);
	}

	bool operator<(const Complex &cpx)const {
		return !(this->operator>=(cpx));
	}
	bool operator<(Complex &&cpx)const {
		return !(this->operator>=(cpx));
	}
	bool operator<(const Ty &ty)const {
		return !(this->operator>=(ty));
	}
	bool operator<(Ty &&ty)const {
		return !(this->operator>=(ty));
	}

	bool operator<=(const Complex &cpx)const {
		return !(this->operator>(cpx));
	}
	bool operator<=(Complex &&cpx)const {
		return !(this->operator>(cpx));
	}
	bool operator<=(const Ty &ty)const {
		return !(this->operator>(ty));
	}
	bool operator<=(Ty &&ty) {
		return !(this->operator<(ty));
	}

	Complex& operator=(const Complex &cpx) {
		this->mReal = cpx.mReal;
		this->mImag = cpx.mImag;
		return *this;
	}
	Complex& operator=(const Ty &ty) {
		this->mReal = ty;
		return *this;
	}

	Complex& operator=(Complex &&cpx) {
		this->mReal = cpx.mReal;
		this->mImag = cpx.mImag;
		return *this;
	}
	Complex& operator=(Ty &&ty) {
		this->mReal = ty;
		return *this;
	}

	Complex operator+(const Complex &cpx)const {
		return Complex(this->mReal + cpx.mReal, this->mImag + cpx.mImag);
	}
	Complex operator+(Complex &&cpx)const {
		return Complex(this->mReal + cpx.mReal, this->mImag + cpx.mImag);
	}
	Complex operator+(const Ty &ty)const {
		return Complex(this->mReal + ty, this->mImag);
	}
	Complex operator+(Ty &&ty)const {
		return Complex(this->mReal + ty, this->mImag);
	}

	Complex& operator+=(const Complex &cpx) {
		return *this = this->operator+(cpx);
	}
	Complex& operator+=(Complex &&cpx) {
		return *this = this->operator+(cpx);
	}
	Complex& operator+=(const Ty &ty) {
		return *this = this->operator+(ty);
	}
	Complex& operator+=(Ty &&ty) {
		return *this = this->operator+(ty);
	}

	Complex operator-(const Complex &cpx)const {
		return Complex(this->mReal - cpx.mReal, this->mImag - cpx.mImag);
	}
	Complex operator-(Complex &&cpx)const {
		return Complex(this->mReal - cpx.mReal, this->mImag - cpx.mImag);
	}
	Complex operator-(const Ty &ty)const {
		return Complex(this->mReal - ty, this->mImag);
	}
	Complex operator-(Ty &&ty)const {
		return Complex(this->mReal - ty, this->mImag);
	}

	Complex& operator-=(const Complex &cpx) {
		return *this = this->operator-(cpx);
	}
	Complex& operator-=(Complex &&cpx) {
		return *this = this->operator-(cpx);
	}
	Complex& operator-=(const Ty &ty) {
		return *this = this->operator-(ty);
	}
	Complex& operator-=(Ty &&ty) {
		return *this = this->operator-(ty);
	}

	Complex operator*(const Complex &cpx)const {
		Ty real = this->mReal*cpx.mReal - this->mImag*cpx.mImag,
			imag = this->mImag*cpx.mReal + this->mReal*cpx.mImag;
		return Complex(real, imag);
	}
	Complex operator*(Complex &&cpx)const {
		Ty real = this->mReal*cpx.mReal - this->mImag*cpx.mImag,
			imag = this->mImag*cpx.mReal + this->mReal*cpx.mImag;
		return Complex(real, imag);
	}
	Complex operator*(const Ty &ty)const {
		return Complex(this->mReal*ty, this->mImag*ty);
	}
	Complex operator*(Ty &&ty)const {
		return Complex(this->mReal*ty, this->mImag*ty);
	}

	Complex& operator*=(const Complex &cpx) {
		return *this = this->operator*(cpx);
	}
	Complex& operator*=(Complex &&cpx) {
		return *this = this->operator*(cpx);
	}
	Complex& operator*=(const Ty &ty) {
		return *this = this->operator*(ty);
	}
	Complex& operator*=(Ty &&ty) {
		return *this = this->operator*(ty);
	}

	Complex operator/(const Complex &cpx)const {
		Ty down = static_cast<Ty>(std::pow(cpx.mReal, 2) + std::pow(cpx.mImag, 2));
		Ty real = (this->mReal*cpx.mReal + this->mImag*cpx.mImag) / down,
			imag = (this->mImag*cpx.mReal - this->mReal*cpx.mImag) / down;
		return Complex(real, imag);
	}
	Complex operator/(Complex &&cpx)const {
		Ty down = static_cast<Ty>(std::pow(cpx.mReal, 2) + std::pow(cpx.mImag, 2));
		Ty real = (this->mReal*cpx.mReal + this->mImag*cpx.mImag) / down,
			imag = (this->mImag*cpx.mReal - this->mReal*cpx.mImag) / down;
		return Complex(real, imag);
	}
	Complex operator/(const Ty &ty)const {
		return Complex(this->mReal / ty, this->mImag / ty);
	}
	Complex operator/(Ty &&ty)const {
		return Complex(this->mReal / ty, this->mImag / ty);
	}

	Complex& operator/=(const Complex &cpx) {
		return *this = this->operator/(cpx);
	}
	Complex& operator/=(Complex &&cpx) {
		return *this = this->operator/(cpx);
	}
	Complex& operator/=(const Ty &ty) {
		return *this = this->operator/(ty);
	}
	Complex& operator/=(Ty &&ty) {
		return *this = this->operator/(ty);
	}

private:
	Ty mReal;
	Ty mImag;
};

template<typename Ty>
inline std::ostream& operator<<(std::ostream &os, const Complex<Ty> &cpx)
{
	if (cpx.mReal != Ty() && cpx.mImag != Ty()) {
		if (cpx.mImag > Ty()) {
			os << cpx.mReal << "+" << cpx.mImag << "i";
		}
		else {
			os << cpx.mReal << cpx.mImag << "i";
		}
	}
	else if (cpx.mReal == Ty() && cpx.mImag != Ty()) {
		os << cpx.mImag << "i";
	}
	else if (cpx.mReal != Ty() && cpx.mImag == Ty()) {
		os << cpx.mReal;
	}
	else {
		os << Ty();
	}
	return os;
}

template<typename Ty>
bool operator==(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx == ty;
}
template<typename Ty>
bool operator==(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx == ty;
}

template<typename Ty>
bool operator!=(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx != ty;
}

template<typename Ty>
bool operator!=(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx != ty;
}

template<typename Ty>
bool operator>(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx <= ty;
}
template<typename Ty>
bool operator>(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx <= ty;
}

template<typename Ty>
bool operator>=(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx < ty;
}
template<typename Ty>
bool operator>=(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx < ty;
}

template<typename Ty>
bool operator<(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx >= ty;
}
template<typename Ty>
bool operator<(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx >= ty;
}

template<typename Ty>
bool operator<=(const Ty ty, const Complex<Ty> &cpx)
{
	return cpx > ty;
}
template<typename Ty>
bool operator<=(const Ty ty, const Complex<Ty> &&cpx)
{
	return cpx > ty;
}

template<typename Ty>
Complex<Ty> operator+(const Ty ty, const Complex<Ty> &cpx) {
	return cpx + ty;
}
template<typename Ty>
Complex<Ty> operator+(const Ty ty, const Complex<Ty> &&cpx) {
	return cpx + ty;
}

template<typename Ty>
Complex<Ty> operator+=(const Ty ty, Complex<Ty> &cpx) {
	return cpx += ty;
}
template<typename Ty>
Complex<Ty> operator+=(const Ty ty, Complex<Ty> &&cpx) {
	return cpx += ty;
}

template<typename Ty>
Complex<Ty> operator-(const Ty ty, const Complex<Ty> &cpx) {
	return cpx - ty;
}
template<typename Ty>
Complex<Ty> operator-(const Ty ty, const Complex<Ty> &&cpx) {
	return cpx - ty;
}

template<typename Ty>
Complex<Ty> operator-=(const Ty ty, Complex<Ty> &cpx) {
	return cpx -= ty;
}
template<typename Ty>
Complex<Ty> operator-=(const Ty ty, Complex<Ty> &&cpx) {
	return cpx -= ty;
}

template<typename Ty>
Complex<Ty> operator*(const Ty ty, const Complex<Ty> &cpx) {
	return cpx * ty;
}
template<typename Ty>
Complex<Ty> operator*(const Ty ty, const Complex<Ty> &&cpx) {
	return cpx * ty;
}

template<typename Ty>
Complex<Ty> operator*=(const Ty ty, Complex<Ty> &cpx) {
	return cpx *= ty;
}
template<typename Ty>
Complex<Ty> operator*=(const Ty ty, Complex<Ty> &&cpx) {
	return cpx *= ty;
}

template<typename Ty>
Complex<Ty> operator/(const Ty ty, const Complex<Ty> &cpx) {
	return cpx / ty;
}
template<typename Ty>
Complex<Ty> operator/(const Ty ty, const Complex<Ty> &&cpx) {
	return cpx / ty;
}

template<typename Ty>
Complex<Ty> operator/=(const Ty ty, Complex<Ty> &cpx) {
	return cpx /= ty;
}
template<typename Ty>
Complex<Ty> operator/=(const Ty ty, Complex<Ty> &&cpx) {
	return cpx /= ty;
}