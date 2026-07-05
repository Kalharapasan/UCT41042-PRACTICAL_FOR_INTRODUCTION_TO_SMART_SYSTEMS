import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../models/street_light_log.dart';

class HistoryTile extends StatelessWidget {
  final StreetLightLog log;
  final bool isLatest;

  const HistoryTile({super.key, required this.log, this.isLatest = false});

  Color get _dotColor {
    switch (log.ledColor) {
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

  @override
  Widget build(BuildContext context) {
    final timeStr =
        DateFormat('HH:mm:ss  dd MMM yyyy').format(log.createdAt);

    return Container(
      margin: const EdgeInsets.only(bottom: 8),
      padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
      decoration: BoxDecoration(
        color: isLatest
            ? Colors.white.withOpacity(0.07)
            : Colors.white.withOpacity(0.03),
        borderRadius: BorderRadius.circular(12),
        border: Border.all(
          color: isLatest
              ? _dotColor.withOpacity(0.3)
              : Colors.white.withOpacity(0.06),
        ),
      ),
      child: Row(
        children: [
          Container(
            width: 10,
            height: 10,
            decoration: BoxDecoration(
              shape: BoxShape.circle,
              color: _dotColor,
              boxShadow: isLatest
                  ? [
                      BoxShadow(
                          color: _dotColor.withOpacity(0.6), blurRadius: 6)
                    ]
                  : null,
            ),
          ),
          const SizedBox(width: 12),
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Row(
                  children: [
                    Text(
                      '${log.intensity}% intensity',
                      style: const TextStyle(
                        color: Colors.white,
                        fontSize: 13,
                        fontWeight: FontWeight.w600,
                      ),
                    ),
                    const SizedBox(width: 8),
                    if (isLatest)
                      Container(
                        padding: const EdgeInsets.symmetric(
                            horizontal: 6, vertical: 2),
                        decoration: BoxDecoration(
                          color: _dotColor.withOpacity(0.15),
                          borderRadius: BorderRadius.circular(4),
                        ),
                        child: Text(
                          'LATEST',
                          style: TextStyle(
                            color: _dotColor,
                            fontSize: 9,
                            fontWeight: FontWeight.w700,
                            letterSpacing: 1,
                          ),
                        ),
                      ),
                  ],
                ),
                const SizedBox(height: 2),
                Text(
                  '${log.conditionLabel}  ·  Street Light ${log.status}',
                  style: TextStyle(
                    color: Colors.white.withOpacity(0.45),
                    fontSize: 11,
                  ),
                ),
              ],
            ),
          ),
          Text(
            timeStr,
            style: TextStyle(
              color: Colors.white.withOpacity(0.3),
              fontSize: 10,
            ),
          ),
        ],
      ),
    );
  }
}
