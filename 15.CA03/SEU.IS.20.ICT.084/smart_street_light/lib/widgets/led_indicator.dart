import 'package:flutter/material.dart';
import '../models/street_light_log.dart';

class LedIndicator extends StatefulWidget {
  final LedColor ledColor;
  final double size;

  const LedIndicator({
    super.key,
    required this.ledColor,
    this.size = 80,
  });

  @override
  State<LedIndicator> createState() => _LedIndicatorState();
}

class _LedIndicatorState extends State<LedIndicator>
    with SingleTickerProviderStateMixin {
  late AnimationController _blinkController;
  late Animation<double> _blinkAnimation;

  @override
  void initState() {
    super.initState();
    _blinkController = AnimationController(
      vsync: this,
      duration: const Duration(milliseconds: 600),
    );
    _blinkAnimation = Tween<double>(begin: 0.2, end: 1.0).animate(
      CurvedAnimation(parent: _blinkController, curve: Curves.easeInOut),
    );
    _startOrStopBlink();
  }

  @override
  void didUpdateWidget(LedIndicator oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.ledColor != widget.ledColor) {
      _startOrStopBlink();
    }
  }

  void _startOrStopBlink() {
    if (widget.ledColor == LedColor.redBlink) {
      _blinkController.repeat(reverse: true);
    } else {
      _blinkController.stop();
      _blinkController.value = 1.0;
    }
  }

  @override
  void dispose() {
    _blinkController.dispose();
    super.dispose();
  }

  Color get _primaryColor {
    switch (widget.ledColor) {
      case LedColor.green:
        return const Color(0xFF00E676);
      case LedColor.blue:
        return const Color(0xFF40C4FF);
      case LedColor.red:
      case LedColor.redBlink:
        return const Color(0xFFFF1744);
      case LedColor.unknown:
        return const Color(0xFF78909C);
    }
  }

  String get _label {
    switch (widget.ledColor) {
      case LedColor.green:
        return 'GREEN';
      case LedColor.blue:
        return 'BLUE';
      case LedColor.red:
        return 'RED';
      case LedColor.redBlink:
        return 'RED BLINK';
      case LedColor.unknown:
        return '—';
    }
  }

  @override
  Widget build(BuildContext context) {
    return AnimatedBuilder(
      animation: _blinkAnimation,
      builder: (context, child) {
        final opacity =
            widget.ledColor == LedColor.redBlink ? _blinkAnimation.value : 1.0;
        return Opacity(
          opacity: opacity,
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              Container(
                width: widget.size,
                height: widget.size,
                decoration: BoxDecoration(
                  shape: BoxShape.circle,
                  color: _primaryColor.withOpacity(0.15),
                  border: Border.all(
                    color: _primaryColor.withOpacity(0.6),
                    width: 2,
                  ),
                  boxShadow: [
                    BoxShadow(
                      color: _primaryColor.withOpacity(0.5 * opacity),
                      blurRadius: 24,
                      spreadRadius: 4,
                    ),
                  ],
                ),
                child: Center(
                  child: Container(
                    width: widget.size * 0.55,
                    height: widget.size * 0.55,
                    decoration: BoxDecoration(
                      shape: BoxShape.circle,
                      color: _primaryColor,
                      boxShadow: [
                        BoxShadow(
                          color: _primaryColor.withOpacity(0.8),
                          blurRadius: 12,
                          spreadRadius: 2,
                        ),
                      ],
                    ),
                  ),
                ),
              ),
              const SizedBox(height: 8),
              Text(
                _label,
                style: TextStyle(
                  color: _primaryColor,
                  fontSize: 11,
                  fontWeight: FontWeight.w700,
                  letterSpacing: 1.5,
                ),
              ),
            ],
          ),
        );
      },
    );
  }
}
