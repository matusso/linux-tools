utils.packages:
  pkg.installed:
    - pkgs:
      - tmux
      - dstat
      - htop
      - iotop
      - pass
      - pwgen

vim:
  pkg.installed:
    - name: {{ pillar['vim'] }}
