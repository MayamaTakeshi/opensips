/*
 * $Id$
 *
 * POSTGRES module, portions of this code were templated using
 * the mysql module, thus it's similarity.
 *
 * Copyright (C) 2003 August.Net Services, LLC
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * ---
 *
 * History
 * -------
 * 2003-04-06 initial code written (Greg Fausak/Andy Fullford)
 *
 */


#ifndef PG_CON_H
#define PG_CON_H

#include "../../db/db_pool.h"
#include "../../db/db_id.h"

#include <time.h>
#include <libpq-fe.h>

/*
 * Postgres specific connection data
 */
struct pg_con {
	struct db_id* id;        /* Connection identifier */
	unsigned int ref;        /* Reference count */
	struct pool_con* next;   /* Next connection in the pool */

	int connected;
	char *sqlurl;		/* the url we are connected to, all connection memory parents from this */
	PGconn *con;		/* this is the postgres connection */
	PGresult *res;		/* this is the current result */
	char**  row;		/* Actual row in the result */
	time_t timestamp;	/* Timestamp of last query */

};

#define CON_SQLURL(db_con)     (((struct pg_con*)((db_con)->tail))->sqlurl)
#define CON_RESULT(db_con)     (((struct pg_con*)((db_con)->tail))->res)
#define CON_CONNECTION(db_con) (((struct pg_con*)((db_con)->tail))->con)
#define CON_CONNECTED(db_con)  (((struct pg_con*)((db_con)->tail))->connected)
#define CON_ROW(db_con)	       (((struct pg_con*)((db_con)->tail))->row)
#define CON_TIMESTAMP(db_con)  (((struct pg_con*)((db_con)->tail))->timestamp)
#define CON_ID(db_con) 	       (((struct pg_con*)((db_con)->tail))->id)

/*
 * Create a new connection structure,
 * open the PostgreSQL connection and set reference count to 1
 */
struct pg_con* db_postgres_new_connection(struct db_id* id);

/*
 * Close the connection and release memory
 */
void db_postgres_free_connection(struct pool_con* con);

#endif /* PG_CON_H */
