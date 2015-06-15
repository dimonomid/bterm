
#line 1 "./htcodec_iso14230.cpp.rl"
/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htcodec_iso14230.h"


/*******************************************************************************
 * AUTO-GENERATED RAGEL DATA
 ******************************************************************************/


#line 21 "./htcodec_iso14230.cpp"
static const char _iso14230_actions[] = {
	0, 1, 0, 1, 5, 1, 6, 1, 
	8, 2, 1, 5, 2, 2, 5, 2, 
	3, 5, 2, 4, 5, 2, 7, 5
	
};

static const char _iso14230_cond_offsets[] = {
	0, 0, 0, 1, 2, 3, 3
};

static const char _iso14230_cond_lengths[] = {
	0, 0, 1, 1, 1, 0, 0
};

static const short _iso14230_cond_keys[] = {
	0u, 255u, 0u, 255u, 0u, 255u, 0
};

static const char _iso14230_cond_spaces[] = {
	0, 1, 4, 0
};

static const char _iso14230_key_offsets[] = {
	0, 0, 0, 2, 4, 10, 13
};

static const short _iso14230_trans_keys[] = {
	512u, 767u, 1024u, 1279u, 2560u, 2815u, 2816u, 3071u, 
	3072u, 3327u, 128u, 129u, 255u, 128u, 129u, 255u, 
	0
};

static const char _iso14230_single_lengths[] = {
	0, 0, 0, 0, 0, 1, 1
};

static const char _iso14230_range_lengths[] = {
	0, 0, 1, 1, 3, 1, 1
};

static const char _iso14230_index_offsets[] = {
	0, 0, 1, 3, 5, 9, 12
};

static const char _iso14230_trans_targs[] = {
	2, 3, 0, 4, 0, 4, 6, 4, 
	0, 1, 2, 0, 1, 2, 0, 0
};

static const char _iso14230_trans_actions[] = {
	12, 15, 7, 18, 7, 5, 21, 5, 
	7, 3, 9, 7, 3, 9, 7, 0
};

static const char _iso14230_to_state_actions[] = {
	0, 0, 0, 0, 0, 1, 1
};

static const char _iso14230_eof_actions[] = {
	0, 7, 7, 7, 7, 7, 0
};

static const int iso14230_start = 6;
static const int iso14230_first_final = 6;
static const int iso14230_error = 0;

static const int iso14230_en_main = 6;
static const int iso14230_en_main_msg_start = 5;


#line 21 "./htcodec_iso14230.cpp.rl"


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTCodec_ISO14230::HTCodec_ISO14230() :
   cur_rx_msg(HTDataMsg()),
   ragel_cs(0)
{
   int cs = ragel_cs;
   
#line 106 "./htcodec_iso14230.cpp"
	{
	cs = iso14230_start;
	}

#line 34 "./htcodec_iso14230.cpp.rl"

   ragel_cs = cs;
}





/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * AUTO-GENERATED RAGEL CODE
 ******************************************************************************/


#line 147 "./htcodec_iso14230.cpp.rl"


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

void HTCodec_ISO14230::addRawRxData(const vector<unsigned char> &data)
{
   const unsigned char *p = data.data();
   const unsigned char *pe = p + data.size();
   int cs = this->ragel_cs;
   const unsigned char *eof = nullptr;
   
#line 156 "./htcodec_iso14230.cpp"
	{
	int _klen;
	unsigned int _trans;
	short _widec;
	const char *_acts;
	unsigned int _nacts;
	const short *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_widec = (*p);
	_klen = _iso14230_cond_lengths[cs];
	_keys = _iso14230_cond_keys + (_iso14230_cond_offsets[cs]*2);
	if ( _klen > 0 ) {
		const short *_lower = _keys;
		const short *_mid;
		const short *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( _widec < _mid[0] )
				_upper = _mid - 2;
			else if ( _widec > _mid[1] )
				_lower = _mid + 2;
			else {
				switch ( _iso14230_cond_spaces[_iso14230_cond_offsets[cs] + ((_mid - _keys)>>1)] ) {
	case 0: {
		_widec = (short)(256u + ((*p) - 0u));
		if ( 
#line 102 "./htcodec_iso14230.cpp.rl"

      //(!tgt_care || fc == tgt_needed);
      //TODO
      1
    ) _widec += 256;
		break;
	}
	case 1: {
		_widec = (short)(768u + ((*p) - 0u));
		if ( 
#line 108 "./htcodec_iso14230.cpp.rl"

      //(!src_care || fc == src_needed);
      //TODO
      1
    ) _widec += 256;
		break;
	}
	case 2: {
		_widec = (short)(1280u + ((*p) - 0u));
		if ( 
#line 114 "./htcodec_iso14230.cpp.rl"

      (rx_user_data_got_len++ < rx_user_data_len)
    ) _widec += 256;
		break;
	}
	case 3: {
		_widec = (short)(1792u + ((*p) - 0u));
		if ( 
#line 118 "./htcodec_iso14230.cpp.rl"

      1/*TODO*/
    ) _widec += 256;
		break;
	}
	case 4: {
		_widec = (short)(2304u + ((*p) - 0u));
		if ( 
#line 114 "./htcodec_iso14230.cpp.rl"

      (rx_user_data_got_len++ < rx_user_data_len)
    ) _widec += 256;
		if ( 
#line 118 "./htcodec_iso14230.cpp.rl"

      1/*TODO*/
    ) _widec += 512;
		break;
	}
				}
				break;
			}
		}
	}

	_keys = _iso14230_trans_keys + _iso14230_key_offsets[cs];
	_trans = _iso14230_index_offsets[cs];

	_klen = _iso14230_single_lengths[cs];
	if ( _klen > 0 ) {
		const short *_lower = _keys;
		const short *_mid;
		const short *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( _widec < *_mid )
				_upper = _mid - 1;
			else if ( _widec > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _iso14230_range_lengths[cs];
	if ( _klen > 0 ) {
		const short *_lower = _keys;
		const short *_mid;
		const short *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( _widec < _mid[0] )
				_upper = _mid - 2;
			else if ( _widec > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _iso14230_trans_targs[_trans];

	if ( _iso14230_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _iso14230_actions + _iso14230_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 1:
#line 62 "./htcodec_iso14230.cpp.rl"
	{
      rx_user_data_len = (*p) & ~0x80;
   }
	break;
	case 2:
#line 66 "./htcodec_iso14230.cpp.rl"
	{
      rx_user_data_len = (*p);
   }
	break;
	case 3:
#line 70 "./htcodec_iso14230.cpp.rl"
	{
      //tgt = fc;
      //TODO
   }
	break;
	case 4:
#line 75 "./htcodec_iso14230.cpp.rl"
	{
      //src = fc;
      //TODO
   }
	break;
	case 5:
#line 80 "./htcodec_iso14230.cpp.rl"
	{
      this->cur_rx_msg.addData(HTDataPart::Type::SERVICE, (*p));
   }
	break;
	case 6:
#line 84 "./htcodec_iso14230.cpp.rl"
	{
      this->cur_rx_msg.addData(HTDataPart::Type::USER, (*p));
   }
	break;
	case 7:
#line 88 "./htcodec_iso14230.cpp.rl"
	{
      /* TODO */
   }
	break;
	case 8:
#line 92 "./htcodec_iso14230.cpp.rl"
	{
      /* TODO */
      p--; {cs = 5; goto _again;}
   }
	break;
#line 359 "./htcodec_iso14230.cpp"
		}
	}

_again:
	_acts = _iso14230_actions + _iso14230_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 58 "./htcodec_iso14230.cpp.rl"
	{
      /* TODO */
   }
	break;
#line 374 "./htcodec_iso14230.cpp"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _iso14230_actions + _iso14230_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 8:
#line 92 "./htcodec_iso14230.cpp.rl"
	{
      /* TODO */
      p--; {cs = 5; goto _again;}
   }
	break;
#line 396 "./htcodec_iso14230.cpp"
		}
	}
	}

	_out: {}
	}

#line 167 "./htcodec_iso14230.cpp.rl"

   ragel_cs = cs;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


