/* Python interface to objfiles.

   Copyright (C) 2008, 2009, 2010 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "defs.h"
#include "python-internal.h"
#include "charset.h"
#include "objfiles.h"
#include "language.h"

typedef struct
{
  PyObject_HEAD

  /* The corresponding objfile.  */
  struct objfile *objfile;

  /* The pretty-printer list of functions.  */
  PyObject *printers;
} objfile_object;

static PyTypeObject objfile_object_type;

static const struct objfile_data *objfpy_objfile_data_key;



/* An Objfile method which returns the objfile's file name, or None.  */
static PyObject *
objfpy_get_filename (PyObject *self, void *closure)
{
  objfile_object *obj = (objfile_object *) self;
  if (obj->objfile && obj->objfile->name)
    return PyString_Decode (obj->objfile->name, strlen (obj->objfile->name),
			    host_charset (), NULL);
  Py_RETURN_NONE;
}

static void
objfpy_dealloc (PyObject *o)
{
  objfile_object *self = (objfile_object *) o;
  Py_XDECREF (self->printers);
  self->ob_type->tp_free ((PyObject *) self);
}

static PyObject *
objfpy_new (PyTypeObject *type, PyObject *args, PyObject *keywords)
{
  objfile_object *self = (objfile_object *) type->tp_alloc (type, 0);
  if (self)
    {
      self->objfile = NULL;

      self->printers = PyList_New (0);
      if (!self->printers)
	{
	  Py_DECREF (self);
	  return NULL;
	}
    }
  return (PyObject *) self;
}

PyObject *
objfpy_get_printers (PyObject *o, void *ignore)
{
  objfile_object *self = (objfile_object *) o;
  Py_INCREF (self->printers);
  return self->printers;
}

static int
objfpy_set_printers (PyObject *o, PyObject *value, void *ignore)
{
  PyObject *tmp;
  objfile_object *self = (objfile_object *) o;
  if (! value)
    {
      PyErr_SetString (PyExc_TypeError,
		       "cannot delete the pretty_printers attribute");
      return -1;
    }

  if (! PyList_Check (value))
    {
      PyErr_SetString (PyExc_TypeError,
		       "the pretty_printers attribute must be a list");
      return -1;
    }

  /* Take care in case the LHS and RHS are related somehow.  */
  tmp = self->printers;
  Py_INCREF (value);
  self->printers = value;
  Py_XDECREF (tmp);

  return 0;
}



/* Clear the OBJFILE pointer in an Objfile object and remove the
   reference.  */
static void
py_free_objfile (struct objfile *objfile, void *datum)
{
  struct cleanup *cleanup;
  objfile_object *object = datum;

  cleanup = ensure_python_env (get_objfile_arch (objfile), current_language);
  object->objfile = NULL;
  Py_DECREF ((PyObject *) object);
  do_cleanups (cleanup);
}

/* Return a borrowed reference to the Python object of type Objfile
   representing OBJFILE.  If the object has already been created,
   return it.  Otherwise, create it.  Return NULL and set the Python
   error on failure.  */
PyObject *
objfile_to_objfile_object (struct objfile *objfile)
{
  objfile_object *object;

  object = objfile_data (objfile, objfpy_objfile_data_key);
  if (!object)
    {
      object = PyObject_New (objfile_object, &objfile_object_type);
      if (object)
	{
	  PyObject *dict;

	  object->objfile = objfile;

	  object->printers = PyList_New (0);
	  if (!object->printers)
	    {
	      Py_DECREF (object);
	      return NULL;
	    }

	  set_objfile_data (objfile, objfpy_objfile_data_key, object);
	}
    }

  return (PyObject *) object;
}

void
gdbpy_initialize_objfile (void)
{
  objfpy_objfile_data_key
    = register_objfile_data_with_cleanup (NULL, py_free_objfile);

  if (PyType_Ready (&objfile_object_type) < 0)
    return;

  Py_INCREF (&objfile_object_type);
  PyModule_AddObject (gdb_module, "Objfile", (PyObject *) &objfile_object_type);
}



static PyGetSetDef objfile_getset[] =
{
  { "filename", objfpy_get_filename, NULL,
    "The objfile's filename, or None.", NULL },
  { "pretty_printers", objfpy_get_printers, objfpy_set_printers,
    "Pretty printers.", NULL },
  { NULL }
};

static PyTypeObject objfile_object_type =
{
  PyObject_HEAD_INIT (NULL)
  0,				  /*ob_size*/
  "gdb.Objfile",		  /*tp_name*/
  sizeof (objfile_object),	  /*tp_basicsize*/
  0,				  /*tp_itemsize*/
  objfpy_dealloc,		  /*tp_dealloc*/
  0,				  /*tp_print*/
  0,				  /*tp_getattr*/
  0,				  /*tp_setattr*/
  0,				  /*tp_compare*/
  0,				  /*tp_repr*/
  0,				  /*tp_as_number*/
  0,				  /*tp_as_sequence*/
  0,				  /*tp_as_mapping*/
  0,				  /*tp_hash */
  0,				  /*tp_call*/
  0,				  /*tp_str*/
  0,				  /*tp_getattro*/
  0,				  /*tp_setattro*/
  0,				  /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT,		  /*tp_flags*/
  "GDB objfile object",		  /* tp_doc */
  0,				  /* tp_traverse */
  0,				  /* tp_clear */
  0,				  /* tp_richcompare */
  0,				  /* tp_weaklistoffset */
  0,				  /* tp_iter */
  0,				  /* tp_iternext */
  0,				  /* tp_methods */
  0,				  /* tp_members */
  objfile_getset,		  /* tp_getset */
  0,				  /* tp_base */
  0,				  /* tp_dict */
  0,				  /* tp_descr_get */
  0,				  /* tp_descr_set */
  0,				  /* tp_dictoffset */
  0,				  /* tp_init */
  0,				  /* tp_alloc */
  objfpy_new,			  /* tp_new */
};
