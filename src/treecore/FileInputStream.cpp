/*
  ==============================================================================

   This file is part of the juce_core module of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission to use, copy, modify, and/or distribute this software for any purpose with
   or without fee is hereby granted, provided that the above copyright notice and this
   permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
   NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
   IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ------------------------------------------------------------------------------

   NOTE! This permissive ISC license applies ONLY to files within the juce_core module!
   All other JUCE modules are covered by a dual GPL/commercial license, so if you are
   using any other modules, be sure to check that you also comply with their license.

   For more details, visit www.juce.com

  ==============================================================================
*/

#include "treecore/FileInputStream.h"

namespace treecore {

int64 treecore_fileSetPosition (void* handle, int64 pos);


//==============================================================================
FileInputStream::FileInputStream (const File& f)
    : file (f),
      fileHandle (nullptr),
      currentPosition (0),
      status (Result::ok())
{
    openHandle();
}

int64 FileInputStream::getTotalLength()
{
    // You should always check that a stream opened successfully before using it!
    treecore_assert (openedOk());

    return file.getSize();
}

int FileInputStream::read (void* buffer, int bytesToRead)
{
    // You should always check that a stream opened successfully before using it!
    treecore_assert (openedOk());

    // The buffer should never be null, and a negative size is probably a
    // sign that something is broken!
    treecore_assert (buffer != nullptr && bytesToRead >= 0);

    const size_t num = readInternal (buffer, (size_t) bytesToRead);
    currentPosition += num;

    return (int) num;
}

bool FileInputStream::isExhausted()
{
    return currentPosition >= getTotalLength();
}

int64 FileInputStream::getPosition()
{
    return currentPosition;
}

bool FileInputStream::setPosition (int64 pos)
{
    // You should always check that a stream opened successfully before using it!
    treecore_assert (openedOk());

    if (pos != currentPosition)
        currentPosition = treecore_fileSetPosition (fileHandle, pos);

    return currentPosition == pos;
}

}
