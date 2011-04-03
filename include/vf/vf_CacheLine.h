// Copyright (C) 2008-2011 by Vincent Falco, All rights reserved worldwide.
// This file is released under the MIT License:
// http://www.opensource.org/licenses/mit-license.php

#ifndef __VF_CACHELINE_VFHEADER__
#define __VF_CACHELINE_VFHEADER__

#include "vf/vf_MemoryAlignment.h"

// Allows turning off of all padding,
// e.g. for memory-constrained systems or testing.
//
#define GLOBAL_PADDING_ENABLED 1

namespace CacheLine {

#if GLOBAL_PADDING_ENABLED

// Pads an object so that it starts on a cache line boundary.
//
template <typename T>
class Aligned
{
public:
  ~Aligned ()
    { ptr ()->~T (); }

  Aligned ()
    { new (ptr ()) T; }

  template <class T1>
  explicit Aligned (const T1& t1)
    { new (ptr ()) T (t1); }

  template <class T1, class T2>
  Aligned  (const T1& t1, const T2& t2)
    { new (ptr ()) T (t1, t2); }

  template <class T1, class T2, class T3>
  Aligned  (const T1& t1, const T2& t2, const T3& t3)
    { new (ptr ()) T (t1, t2, t3); }

  template <class T1, class T2, class T3, class T4>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4)
    { new (ptr ()) T (t1, t2, t3, t4); }

  template <class T1, class T2, class T3, class T4, class T5>
  Aligned  (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5)
    { new (ptr ()) T (t1, t2, t3, t4, t5); }

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Aligned  (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5, const T6& t6)
    { new (ptr ()) T (t1, t2, t3, t4, t5, t6); }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7)
    { new (ptr ()) T (t1, t2, t3, t4, t5, t6, t7); }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7, const T8& t8)
    { new (ptr ()) T (t1, t2, t3, t4, t5, t6, t7, t8); }

  void operator= (T const& other) { *ptr () = other; }

  inline T& operator*  () { return *ptr (); }
  inline T* operator-> () { return  ptr (); }
  inline operator T&   () { return *ptr (); }
  inline operator T*   () { return  ptr (); }

  inline const T& operator*  () const { return *ptr (); }
  inline const T* operator-> () const { return  ptr (); }
  inline operator const T&   () const { return *ptr (); }
  inline operator const T*   () const { return  ptr (); }

private:
  inline T* ptr ()
  {
    return reinterpret_cast <T*> (Memory::pointerAdjustedForAlignment (
                                  m_storage, Memory::cacheLineBytes));
  }
  
  inline T const* ptr () const
  {
    return reinterpret_cast <T*> (Memory::pointerAdjustedForAlignment (
                                  m_storage, Memory::cacheLineBytes));
  }

  char m_storage [ ((sizeof(T) + Memory::cacheLineBytes - 1) /
                   Memory::cacheLineBytes) * Memory::cacheLineBytes];
};

// Holds an object padded it to completely fill a CPU cache line.
// The caller must ensure that this object starts at the beginning
// of a cache line.
//
template <typename T>
class Padded
{
public:
  Padded ()
    { }

  template <class T1>
  explicit Padded (const T1& t1)
    : m_t (t1) { }

  template <class T1, class T2>
  Padded   (const T1& t1, const T2& t2)
    : m_t (t1, t2) { }

  template <class T1, class T2, class T3>
  Padded   (const T1& t1, const T2& t2, const T3& t3)
    : m_t (t1, t2, t3) { }

  template <class T1, class T2, class T3, class T4>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4)
    : m_t (t1, t2, t3, t4) { }

  template <class T1, class T2, class T3, class T4, class T5>
  Padded   (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5)
    : m_t (t1, t2, t3, t4, t5) { }

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Padded   (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5, const T6& t6)
    : m_t (t1, t2, t3, t4, t5, t6) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7)
    : m_t (t1, t2, t3, t4, t5, t6, t7) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7, const T8& t8)
    : m_t (t1, t2, t3, t4, t5, t6, t7, t8) { }

  void operator= (const T& other) { m_t = other; }

  T& operator* () { return m_t; }
  T* operator-> () { return &m_t; }
  operator T& () { return m_t; }
  operator T* () { return &m_t; }

  const T& operator* () const { return m_t; }
  const T* operator-> () const { return &m_t; }
  operator const T& () const { return m_t; }
  operator const T* () const { return &m_t; }

private:
  T m_t;
  char pad [Memory::cacheLineBytes - sizeof(T)];
};

#else

template <typename T>
class Aligned
{
public:
  Aligned ()
    { }

  template <class T1>
  explicit Aligned (const T1& t1)
    : m_t (t1) { }

  template <class T1, class T2>
  Aligned  (const T1& t1, const T2& t2)
    : m_t (t1, t2) { }

  template <class T1, class T2, class T3>
  Aligned  (const T1& t1, const T2& t2, const T3& t3)
    : m_t (t1, t2, t3) { }

  template <class T1, class T2, class T3, class T4>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4)
    : m_t (t1, t2, t3, t4) { }

  template <class T1, class T2, class T3, class T4, class T5>
  Aligned  (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5)
    : m_t (t1, t2, t3, t4, t5) { }

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Aligned  (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5, const T6& t6)
    : m_t (t1, t2, t3, t4, t5, t6) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7)
    : m_t (t1, t2, t3, t4, t5, t6, t7) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8>
  Aligned  (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7, const T8& t8)
    : m_t (t1, t2, t3, t4, t5, t6, t7, t8) { }

  void operator= (const T& other) { m_t = other; }

  T& operator*  () { return  m_t; }
  T* operator-> () { return &m_t; }
  operator T&   () { return  m_t; }
  operator T*   () { return &m_t; }

  const T& operator*  () const { return  m_t; }
  const T* operator-> () const { return &m_t; }
  operator const T&   () const { return  m_t; }
  operator const T*   () const { return &m_t; }

private:
  T m_t;
};

template <typename T>
class Padded
{
public:
  Padded ()
    { }

  template <class T1>
  explicit Padded (const T1& t1)
    : m_t (t1) { }

  template <class T1, class T2>
  Padded   (const T1& t1, const T2& t2)
    : m_t (t1, t2) { }

  template <class T1, class T2, class T3>
  Padded   (const T1& t1, const T2& t2, const T3& t3)
    : m_t (t1, t2, t3) { }

  template <class T1, class T2, class T3, class T4>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4)
    : m_t (t1, t2, t3, t4) { }

  template <class T1, class T2, class T3, class T4, class T5>
  Padded   (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5)
    : m_t (t1, t2, t3, t4, t5) { }

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Padded   (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5, const T6& t6)
    : m_t (t1, t2, t3, t4, t5, t6) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7)
    : m_t (t1, t2, t3, t4, t5, t6, t7) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8>
  Padded   (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7, const T8& t8)
    : m_t (t1, t2, t3, t4, t5, t6, t7, t8) { }

  void operator= (const T& other) { m_t = other; }

  T& operator*  () { return  m_t; }
  T* operator-> () { return &m_t; }
  operator T&   () { return  m_t; }
  operator T*   () { return &m_t; }

  const T& operator*  () const { return  m_t; }
  const T* operator-> () const { return &m_t; }
  operator const T&   () const { return  m_t; }
  operator const T*   () const { return &m_t; }

private:
  T m_t;
};

#endif

//
// Used to remove padding without changing code
//

template <typename T>
class Unpadded
{
public:
  Unpadded ()
    { }

  template <class T1>
  explicit Unpadded (const T1& t1)
    : m_t (t1) { }

  template <class T1, class T2>
  Unpadded (const T1& t1, const T2& t2)
    : m_t (t1, t2) { }

  template <class T1, class T2, class T3>
  Unpadded (const T1& t1, const T2& t2, const T3& t3)
    : m_t (t1, t2, t3) { }

  template <class T1, class T2, class T3, class T4>
  Unpadded (const T1& t1, const T2& t2, const T3& t3, const T4& t4)
    : m_t (t1, t2, t3, t4) { }

  template <class T1, class T2, class T3, class T4, class T5>
  Unpadded (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5)
    : m_t (t1, t2, t3, t4, t5) { }

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Unpadded (const T1& t1, const T2& t2, const T3& t3,
            const T4& t4, const T5& t5, const T6& t6)
    : m_t (t1, t2, t3, t4, t5, t6) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7>
  Unpadded (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7)
    : m_t (t1, t2, t3, t4, t5, t6, t7) { }

  template <class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8>
  Unpadded (const T1& t1, const T2& t2, const T3& t3, const T4& t4,
            const T5& t5, const T6& t6, const T7& t7, const T8& t8)
    : m_t (t1, t2, t3, t4, t5, t6, t7, t8) { }

  void operator= (const T& other) { m_t = other; }

  T& operator*  () { return  m_t; }
  T* operator-> () { return &m_t; }
  operator T&   () { return  m_t; }
  operator T*   () { return &m_t; }

  const T& operator*  () const { return  m_t; }
  const T* operator-> () const { return &m_t; }
  operator const T&   () const { return  m_t; }
  operator const T*   () const { return &m_t; }

private:
  T m_t;
};

}

#endif