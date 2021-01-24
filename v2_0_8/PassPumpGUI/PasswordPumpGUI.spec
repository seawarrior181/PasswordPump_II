# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['cli.py'],
             pathex=['E:\\C\\repos\\murphyrepo\\dev\\GitHub\\PasswordPump_II\\v2_0_8\\PassPumpGUI', 'E:\\C\\repos\\murphyrepo\\dev\\GitHub\\PasswordPump_II\\v2_0_8\\PassPumpGUI'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='PasswordPumpGUI',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=False,
          icon='PasswordPump.ico')
