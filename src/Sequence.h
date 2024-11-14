#ifndef BIOINFOI_SEQUENCE_H
#define BIOINFOI_SEQUENCE_H

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <istream>
#include <ostream>

/**
 * Generic implementation of a sequence class.
 *
 * This class takes an Alphabet as type parameter.
 * The Alphabet defines which characters are representable
 * by the sequence. To do so, the Alphabet class must
 * define a "Characters" enum, which defines the characters
 * stored in the sequence.
 *
 * Additionally, it is assumed to offer the static
 * toChar and toCharacter methods for conversion between
 * chars and the internal representation.
 */
template <typename Alpha> class Sequence
{
  public:
	/**
	 * Some aliases that can be used throughout the program.
	 */
	using Alphabet = Alpha;
	using Characters = typename Alphabet::Characters;

	/**
	 * Defines how the data is stored internally.
	 *
	 * Can be changed if desired.
	 */
	using Container = std::vector<Characters>;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;

	/**
	 * Converts the given string to a sequence.
	 *
	 * @throw InvalidCharacter if a character in seq
	 *        is not valid.
	 */
	static Sequence fromString(const std::string& seq);

	/**
	 * Default constructor.
	 */
	Sequence() {};

	/**
	 * Returns a string representing the sequence.
	 */
	std::string toString() const;

	// Mutable iterator pointing to the begin of the sequence.
	iterator begin();

	// Mutable iterator pointing 'past-the-end' of the sequence.
	iterator end();

	// Constant iterator pointing to the begin of the sequence.
	const_iterator begin() const;

	// Constant iterator pointing 'past-the-end' of the sequence.
	const_iterator end() const;

	// Constant iterator pointing to the begin of the sequence.
	const_iterator cbegin() const;

	// Constant iterator pointing 'past-the-end' of the sequence.
	const_iterator cend() const;

	/**
	 * Returns the length of the sequence
	 */
	size_t size() const;

	/**
	 * Removes all entries from the sequence
	 */
	void clear();

	/**
	 * Make the sequence larger or smaller.
	 *
	 * If the sequence is made larger, new Characters are appended
	 * to the existing sequence, while the old Characters are left intact.
	 * Which Characters are added is undefined.
	 *
	 * Otherwise, only as many characters as needed are removed,
	 * the remaining Characters are again left intact.
	 */
	void resize(size_t i);

	/**
	 * This method ensures, that there are at least i bytes of
	 * internal storage for adding new Characters.
	 */
	void reserve(size_t i);

	/**
	 * Append a single character at the end of the sequence, resulting
	 * in a sequence of size() + 1
	 */
	void push_back(Characters c);

	/**
	 * Get the comment of the sequence.
	 */
	const std::string& getComment() const;

	/**
	 * Set the comment of the sequence.
	 */
	void setComment(const std::string& comment);

	/**
	 * Compares two sequences with offset i.
	 *
	 * @param seq The second sequence with which to compare
	 * @param i   The offset in the first sequence.
	 *
	 * @return true if the first sequence starting at i is
	 *         equal to the second sequence.
	 */
	bool compare(const Sequence& seq, size_t i) const;

	/**
	 * Compute the maximum overlap between the end
	 * of this sequence with the beginning of seq.
	 */
	size_t overlap(const Sequence& seq) const;

	/**
	 * Return a map that contains for each character
	 * how often it is present in the sequence.
	 *
	 * Characters that are not present in the sequence
	 * should not have an entry in the returned map.
	 */
	std::map<Characters, size_t> statistics() const;

	// Operators

	/**
	 * Return the i-th character of the sequence.
	 */
	Characters& operator[](size_t i);

	/**
	 * Return the i-th character of the sequence.
	 */
	Characters operator[](size_t i) const;

	/**
	 * Equality operator.
	 */
	bool operator==(const Sequence&) const;

	/**
	 * Inequality operator.
	 */
	bool operator!=(const Sequence&) const;

	/**
	 * Global output operator
	 */
	template <typename A>
	friend std::ostream& operator<<(std::ostream&, const Sequence<A>&);

	/**
	 * Global input operator
	 */
	template <typename A>
	friend std::istream& operator>>(std::istream&, Sequence<A>&);

  protected:
	/**
	 * The internal storage of the sequence
	 */
	Container storage_;

	/**
	 * An additional string that can be used to store the name of the sequence.
	 */
	std::string comment_;
};

template <typename Alpha>
Sequence<Alpha> Sequence<Alpha>::fromString(const std::string& str)
{
	Sequence seq;

	seq.resize(str.size());

	std::transform(str.begin(), str.end(), seq.begin(), Alpha::toCharacter);

	return seq;
}

template <typename Alpha> std::string Sequence<Alpha>::toString() const
{
	std::string str;
	str.reserve(size());
	
	std::transform(begin(), end(), std::back_inserter(str), Alpha::toChar);

	return str;
}

template <typename Alpha>
typename Sequence<Alpha>::iterator Sequence<Alpha>::begin()
{
	return storage_.begin();
}

template <typename Alpha>
typename Sequence<Alpha>::iterator Sequence<Alpha>::end()
{
	return storage_.end();
}

template <typename Alpha>
typename Sequence<Alpha>::const_iterator Sequence<Alpha>::begin() const
{
	return storage_.begin();
}

template <typename Alpha>
typename Sequence<Alpha>::const_iterator Sequence<Alpha>::end() const
{
	return storage_.end();
}

template <typename Alpha>
typename Sequence<Alpha>::const_iterator Sequence<Alpha>::cbegin() const
{
	return storage_.begin();
}

template <typename Alpha>
typename Sequence<Alpha>::const_iterator Sequence<Alpha>::cend() const
{
	return storage_.end();
}

template <typename Alpha> void Sequence<Alpha>::clear()
{
	return storage_.clear();
}

template <typename Alpha> void Sequence<Alpha>::resize(size_t size)
{
	return storage_.resize(size);
}

template <typename Alpha> void Sequence<Alpha>::reserve(size_t size)
{
	return storage_.reserve(size);
}

template <typename Alpha> size_t Sequence<Alpha>::size() const
{
	return storage_.size();
}

template <typename Alpha> void Sequence<Alpha>::push_back(Characters c)
{
	return storage_.push_back(c);
}

template <typename Alpha> const std::string& Sequence<Alpha>::getComment() const
{
	return comment_;
}

template <typename Alpha>
void Sequence<Alpha>::setComment(const std::string& comment)
{
	comment_ = comment;
}

template <typename Alpha>
bool Sequence<Alpha>::compare(const Sequence& seq, size_t offset) const
{
	if (offset >= size()) {
		return false;
	}

	return std::equal(cbegin() + offset, cend(), seq.cbegin(), seq.cend());
}

template <typename Alpha>
size_t Sequence<Alpha>::overlap(const Sequence& seq) const
{
	for (auto it = cbegin(); it != cend(); ++it) {
		if (std::equal(it, cend(), seq.begin())) {
			return size() - std::distance(cbegin(), it);
		}
	}

	return 0;
}

template <typename Alpha>
std::map<typename Alpha::Characters, size_t> Sequence<Alpha>::statistics() const
{
	std::map<Sequence::Characters, size_t> result;

	for (auto c : storage_) {
		c = Alpha::canonicalize(c);
		++result[c];
	}

	return result;
}

template <typename Alpha>
typename Sequence<Alpha>::Characters& Sequence<Alpha>::operator[](size_t i)
{
	return storage_[i];
}

template <typename Alpha>
typename Sequence<Alpha>::Characters Sequence<Alpha>::operator[](size_t i) const
{
	return storage_[i];
}

template <typename Alpha>
bool Sequence<Alpha>::operator==(const Sequence<Alpha>& seq) const
{
	return storage_ == seq.storage_;
}

template <typename Alpha>
bool Sequence<Alpha>::operator!=(const Sequence<Alpha>& seq) const
{
	return storage_ != seq.storage_;
}

template <typename Alpha>
std::ostream& operator<<(std::ostream& strm, const Sequence<Alpha>& seq)
{
	std::transform(seq.begin(), seq.end(), std::ostream_iterator<char>(strm),
	               Alpha::toChar);

	return strm;
}

template <typename Alpha>
std::istream& operator>>(std::istream& strm, Sequence<Alpha>& seq)
{
	seq.clear();

	char data;
	while ((data = strm.get()) != '\n' && strm.good()) {
		seq.push_back(Alpha::toCharacter(data));
	}

	return strm;
}

#endif // BIOINFOI_SEQUENCE_H
