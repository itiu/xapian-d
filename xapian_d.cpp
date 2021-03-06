using namespace std;

#include <xapian.h>
#include <iostream>
#include <string>
#include <string.h>

char get_err_code (const char* type)
{
    signed char err;
//    cout << "XAPIAN_D:" << type;
if (strcmp (type, (char*)"DatabaseModifiedError") == 0)
    err = -1;
else if (strcmp (type, (char*)"DatabaseLockError") == 0)
    err = -2;
else if (strcmp (type, (char*)"LogicError") == 0)
    err = -3;
else if (strcmp (type, (char*)"AssertionError") == 0)
    err = -4;
else if (strcmp (type, (char*)"InvalidArgumentError") == 0)
    err = -5;
else if (strcmp (type, (char*)"InvalidOperationError") == 0)
    err = -6;
else if (strcmp (type, (char*)"UnimplementedError") == 0) 
    err = -7;
else if (strcmp (type, (char*)"RuntimeError") == 0)
    err = -8;
else if (strcmp (type, (char*)"DatabaseError") == 0)
    err = -9;
else if (strcmp (type, (char*)"DatabaseCorruptError") == 0)
    err = -10;
else if (strcmp (type, (char*)"DatabaseCreateError") == 0)
    err = -11;
else if (strcmp (type, (char*)"DatabaseOpeningError") == 0)
    err = -12;
else if (strcmp (type, (char*)"DatabaseVersionError") == 0) 
    err = -13;
else if (strcmp (type, (char*)"DocNotFoundError") == 0)
    err = -14;
else if (strcmp (type, (char*)"FeatureUnavailableError") == 0)
    err = -15;
else if (strcmp (type, (char*)"InternalError") == 0)
    err = -16;
else if (strcmp (type, (char*)"NetworkError") == 0)
    err = -17;
else if (strcmp (type, (char*)"NetworkTimeoutError") == 0) 
    err = -18;
else if (strcmp (type, (char*)"QueryParserError") == 0)
    err = -19;
else if (strcmp (type, (char*)"RangeError") == 0)
    err = -20;
else if (strcmp (type, (char*)"SerialisationError") == 0) 
    err = -21;

   return err; 
}

class XapianNumberValueRangeProcessor 
{
    public:
	Xapian::NumberValueRangeProcessor *wrapped;    
};


class XapianDocument
{
    private:
        string g_out_str;
	unsigned int g_out_int;

    public:
	Xapian::Document wrapped;

    virtual void get_data (char **out_val, unsigned int **out_val_length, signed char *err)
    {    
	try
	{
	    g_out_str = wrapped.get_data ();
    	    *out_val = &g_out_str[0];
	    g_out_int = g_out_str.size();
	    *out_val_length = &g_out_int;
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_data (const char* _data, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);
	    wrapped.set_data (data);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_boolean_term(const char* _data, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);
	    wrapped.add_boolean_term (data);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_value(Xapian::valueno slot, const char* _data, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);
	    wrapped.add_value (slot, data);   
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }
    
    virtual void add_value(Xapian::valueno slot, int _data, signed char *err)
    {
	try
	{
	    string data = Xapian::sortable_serialise(_data);
	    wrapped.add_value (slot, data);   
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_value(Xapian::valueno slot, long long _data, signed char *err)
    {
	try
	{
	    string data = Xapian::sortable_serialise(_data);
	    wrapped.add_value (slot, data);   
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_value(Xapian::valueno slot, float _data, signed char *err)
    {
	try
	{
	    string data = Xapian::sortable_serialise(_data);
	    wrapped.add_value (slot, data);   
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_value(Xapian::valueno slot, double _data, signed char *err)
    {
	try
	{
	    string data = Xapian::sortable_serialise(_data);
	    wrapped.add_value (slot, data);   
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    ~XapianDocument ()
    {
//	    cout << "~XapianDocument ()" << endl; 
    }

};


class XapianMSetIterator
{
    private:
        string g_out_str;
        unsigned int g_out_int;

    public:
        Xapian::doccount index;
        Xapian::MSet* mset;

    friend class Xapian::MSet;

    ~XapianMSetIterator ()
    {
//	 cout << "~XapianMSetIterator ()" << endl; 
    }

    virtual unsigned int get_documentid (signed char *err)
    {
	try
	{
	    Xapian::docid id = mset->get_id_by_index(index);
	    *err = 0;
	    return id;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return 0;
	}
    }	

    virtual XapianDocument* get_document (signed char *err)
    {
	try
	{
	    Xapian::Document document = mset->get_doc_by_index(index);
	    XapianDocument* xd = new XapianDocument ();
	    xd->wrapped = document;
	    *err = 0;
	    return xd;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }	

    virtual void get_document_data (char **out_val, unsigned int **out_val_length, signed char *err)
    {
	try
	{
	    Xapian::Document document = mset->get_doc_by_index(index);

            g_out_str = document.get_data ();

            *out_val = &g_out_str[0];
            g_out_int = g_out_str.size();
            *out_val_length = &g_out_int;

	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }	

    virtual void next (signed char *err)
    {
	try
	{
	    if (mset->size () > index)
	    {
		index++;
	    }
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }	

    virtual bool is_next (signed char *err)
    {
	try
	{
	    *err = 0;
	    if (mset->size () > index)
		return true;
	    else
		return false;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return false;
	}
    }	

//    virtual ~XapianMSetIterator (); 

};

class XapianMSet
{
    public:
	Xapian::MSet wrapped;

    ~XapianMSet ()
    {
//	 cout << "~XapianMSet ()" << endl; 
    }

    virtual int get_matches_estimated (signed char *err)
    {
	try
	{
	    *err = 0;
	    return wrapped.get_matches_estimated ();
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return 0;
	}
    }

    virtual int size (signed char *err)
    {
	try
	{
	    *err = 0;
	    return wrapped.size ();
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return 0;
	}
    }

    virtual XapianMSetIterator* iterator (signed char *err)
    {
	try
	{
	    XapianMSetIterator* it = new XapianMSetIterator ();
	    it->index = 0;
	    it->mset = &wrapped;
	    *err = 0;
	    return it;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

//    virtual ~XapianMSet ();
};

class XapianQuery
{
    private:
        string g_out_str;
        unsigned int g_out_int;

    public:
	Xapian::Query query;

    XapianQuery () : query ()
    {
    }

    XapianQuery (const char* _str, unsigned long long _str_len) 
    {
	string str (_str, (unsigned long)_str_len);
	Xapian::Query _query (str);
	query = _query;
    }

    XapianQuery (int op_, int slot, const char* _str, unsigned long long _str_len) 
    {
	string str (_str, (unsigned long)_str_len);
	Xapian::Query _query ((Xapian::Query::op)op_, slot, str);
	query = _query;
    }

    XapianQuery (int op_, int slot, double _begin, double _end) 
    {
	string begin = Xapian::sortable_serialise(_begin);
	string end = Xapian::sortable_serialise(_end);
	Xapian::Query _query ((Xapian::Query::op)op_, slot, begin, end);
	query = _query;
    }

    XapianQuery (int op_, int slot, double _value) 
    {
	string value = Xapian::sortable_serialise(_value);
	Xapian::Query _query ((Xapian::Query::op)op_, slot, value);
	query = _query;	
    }

//    XapianQuery (int op_, XapianQuery* left, XapianQuery* right) 
//    {
//	query = *new Xapian::Query ((Xapian::Query::op)op_, left->query, right->query);
//    }

    virtual void get_description (char **out_val, unsigned int **out_val_length, signed char *err)
    {
	try
	{
	    g_out_str = query.get_description ();

            *out_val = &g_out_str[0];
            g_out_int = g_out_str.size();
            *out_val_length = &g_out_int;

	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void serialise (char **out_val, unsigned int **out_val_length, signed char *err)
    {
	try
	{
	    g_out_str = query.serialise ();

            *out_val = &g_out_str[0];
            g_out_int = g_out_str.size();
            *out_val_length = &g_out_int;

	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual XapianQuery* add_right_query (int op_, XapianQuery* _right, signed char *err)
    {
	try
	{
	    XapianQuery* _new = new XapianQuery ();
	    Xapian::Query _query ((Xapian::Query::op)op_, query, _right->query);
	    _new->query = _query;

	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual int  get_length (signed char *err)
    {
	try
	{
	    int count = query.get_length ();

	    *err = 0;
	    return count;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return -1;
	}
    }

     ~XapianQuery () 
    {
//	    cout << "~XapianQuery ()" << endl; 
    }

};

class XapianMultiValueKeyMaker
{
    public:
        Xapian::MultiValueKeyMaker wrapped;

    XapianMultiValueKeyMaker ()
    {
    }

    virtual void add_value (int pos, signed char *err)
    {
	try
	{
    	    wrapped.add_value (pos);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }
    
    virtual void add_value (int pos, bool asc_desc, signed char *err)
    {
	try
	{
    	    wrapped.add_value (pos, asc_desc);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

//    virtual ~XapianMultiValueKeyMaker ();
};

class XapianEnquire
{
    public:
	Xapian::Enquire* enquire;

    virtual void set_query(XapianQuery* query, signed char *err)
    {
	try
	{
	    enquire->set_query(query->query);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual XapianMSet* get_mset(int from, int size, signed char *err)
    {
	try
	{
	    Xapian::MSet mset = enquire->get_mset(from, size);

	    XapianMSet* _mset = new XapianMSet ();
	    _mset->wrapped = mset;
            *err = 0;
	    return _mset;
        }
        catch (Xapian::Error ex)
        {
            *err = get_err_code (ex.get_type ());
	    return NULL;
        }
    }

    virtual void set_sort_by_key(XapianMultiValueKeyMaker* sorter, bool p, signed char *err)
    {
	try
	{
	    enquire->set_sort_by_key(&(sorter->wrapped), p);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void clear_matchspies(signed char *err)
    {
	try
	{
	    enquire->clear_matchspies();
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

//    virtual ~XapianEnquire ();

};

class XapianWritableDatabase
{
 public:
    Xapian::WritableDatabase* db;

    virtual XapianEnquire* new_Enquire(signed char *err)
    {
        try
        {
            Xapian::Enquire* enquire = new Xapian::Enquire (*db);
            XapianEnquire* _new = new XapianEnquire ();
            _new->enquire = enquire;
            *err = 0;
            return _new;
        }
        catch (Xapian::Error ex)
        {
            *err = get_err_code (ex.get_type ());
            return NULL;
        }
    }

    virtual Xapian::docid add_document (XapianDocument doc, signed char *err)
    {
	try
	{
	    Xapian::docid id = db->add_document (doc.wrapped);
	    *err = 0;
	    return id;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return 0;	
	}
    }

    virtual Xapian::docid replace_document(const char* _unique_term, unsigned long long _unique_term_len, XapianDocument document, signed char *err)
    {
	try
	{
    	    std::string unique_term (_unique_term, (unsigned long)_unique_term_len);

	    *err = 0;
	    return db->replace_document (unique_term, document.wrapped);
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return 0;
	}
    }

    virtual void delete_document (const char* _unique_term, unsigned long long _unique_term_len, signed char *err)
    {
	try
	{
    	    std::string unique_term (_unique_term, (unsigned long)_unique_term_len);

	    db->delete_document (unique_term);
	    *err = 0;
	    return;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return;
	}
    }

    virtual void commit(signed char *err)
    {
	try
	{
	    db->commit ();		
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void close(signed char *err)
    {
	try
	{
	    db->close ();
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void reopen(signed char *err)
    {
	try
	{
	    db->reopen ();
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

//    virtual ~XapianWritableDatabase ();
};

class XapianTermIterator
{
    private:
        string g_out_str;
        unsigned int g_out_int;

    public:
	Xapian::TermIterator begin;
	Xapian::TermIterator end;
	Xapian::TermIterator current;

    virtual void reset (signed char *err)
    {
	try
	{
	    current = begin;
	    
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void next (signed char *err)
    {
	try
	{
	    if (current != end)
		++current;
	    
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }	

    virtual bool is_next (signed char *err)
    {
	try
	{
	    *err = 0;
	    if (current != end)
		return true;
	    else
		return false;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return false;
	}
    }	

    virtual void get_term (char **out_val, unsigned int **out_val_length, signed char *err)
    {
	try
	{
            g_out_str = *current;

            *out_val = &g_out_str[0];
            g_out_int = g_out_str.size();
            *out_val_length = &g_out_int;

	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }	

//    virtual ~XapianTermIterator();
};

class XapianDatabase
{
 public:
    Xapian::Database* db;

    virtual XapianEnquire* new_Enquire(signed char *err)
    {
	try
	{
	    Xapian::Enquire* enquire = new Xapian::Enquire (*db);
	    XapianEnquire* _new = new XapianEnquire ();
	    _new->enquire = enquire;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual void close(signed char *err)
    {
	try
	{
	    db->close ();
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void reopen(signed char *err)
    {
	try
	{
	    db->reopen ();
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual XapianTermIterator* allterms (const char* prefix, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (prefix, (unsigned long)_data_len);

	    Xapian::TermIterator begin = db->allterms_begin (data);
	    Xapian::TermIterator end = db->allterms_end (data);
	    XapianTermIterator* _ti = new XapianTermIterator ();
	    _ti->begin = begin;
	    _ti->current = begin;
	    _ti->end = end;
	    *err = 0;
	    return _ti;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual void add_database (XapianDatabase* add_db, signed char *err)
    {
	try
	{
	    db->add_database (*(add_db->db));
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

};


class XapianStem
{
    public:
	Xapian::Stem* stemmer;
};

class XapianTermGenerator
{
    public:
        Xapian::TermGenerator *wrapped;

    virtual void set_stemmer(XapianStem* stemmer, signed char *err)
    {
	try
	{
	    wrapped->set_stemmer (*stemmer->stemmer);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_document (XapianDocument doc, signed char *err)
    {
	try
	{
	    wrapped->set_document (doc.wrapped);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_text (const char* _data, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);

	    wrapped->index_text (data);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_text (const char* _data, unsigned long long _data_len, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_text_without_positions (const char* _data, unsigned long long _data_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);

	    wrapped->index_text_without_positions (data);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_text_without_positions (const char* _data, unsigned long long _data_len, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    std::string data (_data, (unsigned long)_data_len);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text_without_positions (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_data(int _data, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    string data = Xapian::sortable_serialise(_data);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_data(long long _data, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    string data = Xapian::sortable_serialise(_data);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_data(float _data, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    string data = Xapian::sortable_serialise(_data);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void index_data(double _data, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
    	    string data = Xapian::sortable_serialise(_data);
    	    std::string prefix (_prefix, (unsigned long)_prefix_len);

	    wrapped->index_text (data, 1, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

};

class XapianQueryParser
{
    public:
	Xapian::QueryParser* qp;

    virtual void set_stemmer(XapianStem* stemmer, signed char *err)
    {
	try
	{
	    qp->set_stemmer (*stemmer->stemmer);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_database(XapianDatabase* db, signed char *err)
    {
	try
	{
	    qp->set_database (*db->db);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_database(XapianWritableDatabase* db, signed char *err)
    {
	try
	{
	    qp->set_database (*db->db);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_stemming_strategy(Xapian::QueryParser::stem_strategy strategy, signed char *err)
    {
	try
	{
	    qp->set_stemming_strategy (strategy);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual XapianQuery* parse_query(const char* _query_string, unsigned long long _query_string_len, signed char *err)
    {
	try
	{
	    std::string query_string (_query_string, (unsigned long)_query_string_len);
	    Xapian::Query xq = qp->parse_query(query_string);
	    XapianQuery* _xq = new XapianQuery ();
	    _xq->query = xq;
	    *err = 0;
	    return _xq;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual XapianQuery* parse_query(const char* _query_string, unsigned long long _query_string_len, unsigned flags, signed char *err)
    {
	try
	{
	    std::string query_string (_query_string, (unsigned long)_query_string_len);
	    Xapian::Query xq = qp->parse_query(query_string, flags);
	    XapianQuery* _xq = new XapianQuery ();
	    _xq->query = xq;
	    *err = 0;
	    return _xq;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual XapianQuery* parse_query(const char* _query_string, unsigned long long _query_string_len, unsigned flags, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
	    std::string query_string (_query_string, (unsigned long)_query_string_len);
	    std::string prefix (_prefix, (unsigned long)_prefix_len);
	    Xapian::Query xq = qp->parse_query(query_string, flags, prefix);
	    XapianQuery* _xq = new XapianQuery ();
	    _xq->query = xq;
	    *err = 0;
	    return _xq;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
    }

    virtual void add_prefix (const char* _field, unsigned long long _field_len, const char* _prefix, unsigned long long _prefix_len, signed char *err)
    {
	try
	{
	    std::string field (_field, (unsigned long)_field_len);
	    std::string prefix (_prefix, (unsigned long)_prefix_len);
	    qp->add_prefix (field, prefix);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void add_valuerangeprocessor (XapianNumberValueRangeProcessor *pp, signed char *err)
    {
	try
	{
	    qp->add_valuerangeprocessor (pp->wrapped);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

    virtual void set_max_wildcard_expansion (int limit, signed char *err)
    {
	try
	{
	    qp->set_max_wildcard_expansion (limit);
	    *err = 0;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	}
    }

};

///////////////////////////////////////////////////////////////////////////////////////
const int BRASS = 1;
const int CHERT = 2;
const int IN_MEMORY = 3;

XapianDatabase* new_Database(const char* _path, unsigned int _path_len, int db_type, signed char *err)
{
	try
	{
    	    std::string path (_path, (unsigned long)_path_len);

    	    Xapian::Database* db;
    	     db = new Xapian::Database(path);
//	    if (db_type == BRASS)
//    	     db = new Xapian::Database(Xapian::Brass::open(path));
//	    else if (db_type == CHERT)
//    	     db = new Xapian::Database(Xapian::Chert::open(path));
//	    else if (db_type == IN_MEMORY)
//    	     db = new Xapian::Database(Xapian::InMemory::open());


    	    XapianDatabase* _new = new XapianDatabase ();
    	    _new->db = db;
	    *err = 0;
        return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianDatabase* new_Database(signed char *err)
{
	try
	{
    	    Xapian::Database* db;
    	     db = new Xapian::Database();

    	    XapianDatabase* _new = new XapianDatabase ();
    	    _new->db = db;
	    *err = 0;
        return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}


XapianWritableDatabase* new_WritableDatabase(const char* _path, unsigned int _path_len, int action, int db_type, signed char *err)
{
	try
	{
    	    std::string path (_path, (unsigned long)_path_len);

    	    Xapian::WritableDatabase* db;
	    db = new Xapian::WritableDatabase(path, action);
//	    if (db_type == BRASS)
//    	     db = new Xapian::WritableDatabase(Xapian::Brass::open(path, action));
//	    else if (db_type == CHERT)
//    	     db = new Xapian::WritableDatabase(Xapian::Chert::open(path, action));
//	    else if (db_type == IN_MEMORY)
//    	     db = new Xapian::WritableDatabase(Xapian::InMemory::open());

    	    XapianWritableDatabase* _new = new XapianWritableDatabase ();
    	    _new->db = db;
    	    *err = 0;
    	    return _new;
        }
        catch (Xapian::Error ex)
        {
            *err = get_err_code (ex.get_type ());
	    return NULL;
        }

}

XapianQueryParser* new_QueryParser(signed char *err)
{
	try
	{
	    Xapian::QueryParser* qp = new Xapian::QueryParser ();
	    XapianQueryParser* _new = new XapianQueryParser ();
	    _new->qp = qp;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianStem* new_Stem(char* _language, unsigned int _language_len, signed char *err)
{

	try
	{
	    string language (_language, (unsigned long)_language_len);
	    Xapian::Stem* stemmer = new Xapian::Stem (language);
	    XapianStem* _new = new XapianStem ();
	    _new->stemmer = stemmer;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianTermGenerator* new_TermGenerator(signed char *err)
{
	try
	{
	    Xapian::TermGenerator* termgenerator = new Xapian::TermGenerator ();
	    XapianTermGenerator* _new = new XapianTermGenerator ();
	    _new->wrapped = termgenerator;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianDocument* new_Document(signed char *err)
{
	try
	{
	    XapianDocument* _new = new XapianDocument ();
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianMultiValueKeyMaker* new_MultiValueKeyMaker (signed char *err)
{
	try
	{
	    XapianMultiValueKeyMaker* _new = new XapianMultiValueKeyMaker ();
//	    Xapian::MultiValueKeyMaker mvk = Xapian::MultiValueKeyMaker ();
//	    _new->wrapped = mvk;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianNumberValueRangeProcessor* new_NumberValueRangeProcessor (int slot, const char* _str, unsigned long long _str_len, bool prefix, signed char *err)
{
	try
	{
	    string str (_str, (unsigned long)_str_len);
	    XapianNumberValueRangeProcessor* _new = new XapianNumberValueRangeProcessor ();
	    Xapian::NumberValueRangeProcessor* xnvrp = new Xapian::NumberValueRangeProcessor (slot, str, prefix);
	    _new->wrapped = xnvrp;
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianQuery* new_Query(signed char *err)
{
	try
	{
	    XapianQuery* _new = new XapianQuery ();
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianQuery* new_Query(const char* _str, unsigned int _str_len, signed char *err)
{
	try
	{
	    XapianQuery* _new = new XapianQuery (_str, _str_len);
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianQuery* new_Query_range(int op_, int slot, double _begin, double _end, signed char *err)
{
	try
	{
	    XapianQuery* _new = new XapianQuery (op_, slot, _begin, _end);
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

XapianQuery* new_Query_double(int op_, int slot, double _value, signed char *err)
{
	try
	{
	    XapianQuery* _new = new XapianQuery (op_, slot, _value);
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

// must be OP_VALUE_GE or OP_VALUE_LE. 
XapianQuery* new_Query_equal(int op_, int slot, const char* _str, unsigned long long _str_len, signed char *err)
{
	try
	{
	    XapianQuery* _new = new XapianQuery (op_, slot, _str, _str_len);
	    *err = 0;
	    return _new;
	}
	catch (Xapian::Error ex)
	{	    
	    *err = get_err_code (ex.get_type ());
	    return NULL;
	}
}

///////////////////
        string gg_out_str;
        unsigned int gg_out_int;

void sortable_serialise (double value, char **out_val, unsigned int **out_val_length, signed char *err)
{

    try
    {
    	gg_out_str = Xapian::sortable_serialise(value);

        *out_val = &gg_out_str[0];
        gg_out_int = gg_out_str.size();
        *out_val_length = &gg_out_int;
            
        *err = 0;
    }   
    catch (Xapian::Error ex)
    {   
        *err = get_err_code (ex.get_type ());
    }   
}


void destroy_Database(XapianDatabase* db)
{
    if (db != NULL)
        delete db;
}

void destroy_Document(XapianDocument* doc)
{
    if (doc != NULL)
        delete doc;
}

void destroy_MSet(XapianMSet* mset)
{
    if (mset != NULL)
	delete mset;
}

void destroy_MSetIterator(XapianMSetIterator* msetit)
{
    if (msetit != NULL)
        delete msetit;
}

void destroy_Query (XapianQuery* query)
{
    if (query != NULL)
	delete query;
}

void destroy_Enquire (XapianEnquire* enquire)
{
    if (enquire != NULL)
	delete enquire;
}

void destroy_MultiValueKeyMaker (XapianMultiValueKeyMaker* sorter)
{
    if (sorter != NULL)
	delete sorter;
}
