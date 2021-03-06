# Copyright 2017 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os
import sys
import unittest

import PRESUBMIT

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import PRESUBMIT_test_mocks


class CheckTODOFormatTest(unittest.TestCase):
  """Test the _CheckBugInToDo presubmit check."""

  def testTODOs(self):
    bad_lines = ['TO''DO(ldap): fix this',
                 'TO''DO(ladp): see crbug.com/8675309',
                 'TO''DO(8675309): fix this',
                 'TO''DO(http://crbug.com/8675309): fix this',
                 'TO''DO( crbug.com/8675309): fix this',
                 'TO''DO(crbug/8675309): fix this',
                 'TO''DO(crbug.com): fix this']
    good_lines = ['TO''DO(crbug.com/8675309): fix this',
                  'TO''DO(crbug.com/8675309): fix this (please)']
    mock_input = PRESUBMIT_test_mocks.MockInputApi()
    mock_input.files = [PRESUBMIT_test_mocks.MockFile(
        'ios/path/foo_controller.mm', bad_lines + good_lines)]
    mock_output = PRESUBMIT_test_mocks.MockOutputApi()
    errors = PRESUBMIT._CheckBugInToDo(mock_input, mock_output)
    self.assertEqual(len(errors), 1)
    self.assertEqual('error', errors[0].type)
    self.assertTrue('without bug numbers' in errors[0].message)
    error_lines = errors[0].message.split('\n')
    self.assertEqual(len(error_lines), len(bad_lines) + 2)


if __name__ == '__main__':
  unittest.main()
